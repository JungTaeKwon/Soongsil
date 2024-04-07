--Create stadiums table
Create Table Stadiums(
Sid             Number(5),
Stadiumname     Varchar(20),
Location        Varchar(20),
Primary Key     (Sid)
);

--Create teams table
Create Table Teams(
Teamname Varchar2(20) ,
Wins                 Number(5),
Loses                Number(5),
Sid                 Number(5),
Teamwinrate          Number(4,3),
Primary Key (Teamname),
Foreign Key (Sid) References Stadiums,
Check(Teamwinrate Is Null Or (Teamwinrate >= 0.000 And Teamwinrate <= 1.000))
);

--Create games table
Create Table Games(
Gid                    Number(5),
Hometeam               Varchar2(20),
Awayteam               Varchar2(20),
Matchdate              Date,
Sid                    Number(5),
Hometeamscore          Number(5),
Awayteamscore          Number(5),
Primary Key (Gid),
Foreign Key(Hometeam) References Teams,
Foreign Key(Awayteam) References Teams,
Foreign Key(Sid) References Stadiums
);

--Create sequences
Create Sequence Stadiumssequ Start With 1 Increment By 1;
Create Sequence Gamessequ Start With 10 Increment By 1;

--Insert stadiums tuples
Insert Into Stadiums Values (Stadiumssequ.Nextval,'잠실야구장','잠실');
Insert Into Stadiums Values (Stadiumssequ.Nextval,'랜더스필드','인천');
Insert Into Stadiums Values (Stadiumssequ.Nextval,'창원NC파크','창원');
Insert Into Stadiums Values (Stadiumssequ.Nextval,'KT위즈파크','수원');

--Insert teams tuples
Insert Into Teams Values('LG',3,2,1,0.6);
Insert Into Teams Values('SSG',1,4,2,0.2);
Insert Into Teams Values('두산',2,1,1,0.667);
Insert Into Teams Values('NC',3,2,3,0.6);
Insert Into Teams Values('KT',2,2,4,0.5);

--Insert games tuples
Insert Into Games Values(Gamessequ.Nextval,'두산','KT','2023-04-21',1,6,10);
Insert Into Games Values(Gamessequ.Nextval,'KT','SSG','2023-04-20',4,5,8);
Insert Into Games Values(Gamessequ.Nextval,'LG','NC','2023-04-20',1,9,4);
Insert Into Games Values(Gamessequ.Nextval,'KT','SSG','2023-04-19',4,5,2);
Insert Into Games Values(Gamessequ.Nextval,'LG','NC','2023-04-19',1,7,5);
Insert Into Games Values(Gamessequ.Nextval,'KT','SSG','2023-04-18',4,4,2);
Insert Into Games Values(Gamessequ.Nextval,'LG','NC','2023-04-18',1,4,6);
Insert Into Games Values(Gamessequ.Nextval,'LG','두산','2023-04-16',1,5,10);
Insert Into Games Values(Gamessequ.Nextval,'SSG','NC','2023-04-16',2,5,10);
Insert Into Games Values(Gamessequ.Nextval,'LG','두산','2023-04-15',1,3,1);
Insert Into Games Values(Gamessequ.Nextval,'SSG','NC','2023-04-15',2,0,1);


-- Create trigger using “referencing” and “when” to update teams table based on game results
Create Or Replace Trigger New_Games_Update
After Insert On Games
Referencing New As New_Row
For Each Row
When (New_Row.Hometeamscore Is Not Null And New_Row.Awayteamscore Is Not Null)
Declare
  Home_Team_Wins Number(5);
  Home_Team_Loses Number(5);
  Home_Team_Rate Number(4, 3);
  Away_Team_Wins Number(5);
  Away_Team_Loses Number(5);
  Away_Team_Rate Number(4, 3);
Begin
  -- Retrieve home team's current wins, loses, and winrate
  Select Wins, Loses, Teamwinrate Into Home_Team_Wins, Home_Team_Loses, Home_Team_Rate
  From Teams
  Where Teamname = :New_Row.Hometeam;

  -- Retrieve away team's current wins, loses, and winrate
  Select Wins, Loses, Teamwinrate Into Away_Team_Wins, Away_Team_Loses, Away_Team_Rate
  From Teams
  Where Teamname = :New_Row.Awayteam;

  -- Update home team's wins, loses, and winrate based on game result
  If :New_Row.Hometeamscore > :New_Row.Awayteamscore Then
    Home_Team_Wins := Home_Team_Wins + 1;
  Else
    Home_Team_Loses := Home_Team_Loses + 1;
  End If;

  -- Update away team's wins, loses, and winrate based on game result
  If :New_Row.Awayteamscore > :New_Row.Hometeamscore Then
    Away_Team_Wins := Away_Team_Wins + 1;
  Else
    Away_Team_Loses := Away_Team_Loses + 1;
  End If;

  -- Calculate and update home team's winrate
  Home_Team_Rate := Home_Team_Wins / (Home_Team_Wins + Home_Team_Loses);

  -- Calculate and update away team's winrate
  Away_Team_Rate := Away_Team_Wins / (Away_Team_Wins + Away_Team_Loses);

  -- Update home team's wins, loses, and winrate in teams table
  Update Teams
  Set Wins = Home_Team_Wins, Loses = Home_Team_Loses, Teamwinrate = Home_Team_Rate
  Where Teamname = :New_Row.Hometeam;

  -- Update away team's wins, loses, and winrate in teams table
  Update Teams
  Set Wins = Away_Team_Wins, Loses = Away_Team_Loses, Teamwinrate = Away_Team_Rate
  Where Teamname = :New_Row.Awayteam;
End;
/

  -- Create an updatable view with check option that describes high winning rate teams( winrate> 0.5)
Create Or Replace View High_Winningrate_Teams_View As
Select Teamname,Teamwinrate
From Teams
Where Teamwinrate >= 0.500
Order By Teamwinrate Desc
With Check Option;


Select '1. Nested subquery' From Dual;
Select 'ANY(SOME) : The teams that has ever won a game where LG is a home team' From Dual;
Select Awayteam, Gid
From Games
Where Games.Gid = Any (Select Gid
                       From Games
                       Where Hometeam='LG' And Hometeamscore < Awayteamscore);

Select 'ALL : The teams with a lower winning rate than teams using 잠실야구장 as home stadium' From Dual;
Select Teamname, Teamwinrate
From Teams
Where Teamwinrate < All (Select Teamwinrate
                         From Teams
                         Where Sid=1);



Select '2. Correlated subquery : teams using the same stadium' From Dual;
Select Teamname, (Select Stadiumname From Stadiums Where T1.Sid=Stadiums.Sid)
From Teams T1
Where Exists (Select Sid
             From Teams T2
             Where T1.Sid=T2.Sid And T1.Teamname!=T2.Teamname);

Select '3. Ranking by number of wins' From Dual;
Select Teamname, Wins , Rank() Over (Order By Wins Desc) As Srank
From Teams
Order By Srank;


Select '4. The effect of trigger and view' From Dual;
Select 'Before inserting into games table' From Dual;
Select 'teams table' From Dual;
Select Teamname, Teamwinrate From Teams;
Select 'High_Winning_Rate view' From Dual;
Select * From High_Winningrate_Teams_View;

Insert Into Games Values(Gamessequ.Nextval,'LG','SSG','2023-04-25',1,5,4);
Insert Into Games Values(Gamessequ.Nextval,'LG','SSG','2023-04-26',1,3,5);
Insert Into Games Values(Gamessequ.Nextval,'LG','SSG','2023-04-27',1,6,3);

Select 'After inserting into games table' From Dual;
Select 'teams table' From Dual;
Select Teamname, Teamwinrate From Teams;
Select 'High_Winning_Rate view' From Dual;
Select * From High_Winningrate_Teams_View;

--The effect of view with ‘check option'
Insert Into High_Winningrate_Teams_View Values('NewTeam',0.499);