//2023-04-21 시점에서 KBO 순위 1~5등팀들의 일주일 치 상대전적 분석 데이터베이스
//Create stadiums table
Create table stadiums(
sId             NUMBER(5),
stadiumName     VARCHAR(20),
location        VARCHAR(20),
Primary key     (sId)
);

//Create teams table
Create table teams(
teamName VARCHAR2(20) ,
wins                 NUMBER(5),
loses                NUMBER(5),   
sId                 NUMBER(5),
teamWinRate          NUMBER(4,3),
Primary key (teamName),
Foreign key (sID) references stadiums,
check(teamWinRate IS NULL OR (teamWinRate >= 0.000 AND teamWinRate <= 1.000))
);

//Create games table
Create table games(
gId                    NUMBER(5),
homeTeam               VARCHAR2(20),
awayTeam               VARCHAR2(20),
matchDate              date,
sId                    NUMBER(5),
homeTeamScore          NUMBER(5),   
awayTeamScore          NUMBER(5),
Primary key (gID),
foreign key(homeTeam) references teams,
foreign key(awayTeam) references teams,
foreign key(sID) references stadiums
);

//Create sequences
create sequence stadiumsSequ start with 1 increment by 1;
create sequence gamesSequ start with 10 increment by 1;

//Insert stadiums tuples
insert into stadiums values (stadiumsSequ.nextval,'잠실야구장','잠실');
insert into stadiums values (stadiumsSequ.nextval,'랜더스필드','인천');
insert into stadiums values (stadiumsSequ.nextval,'창원NC파크','창원');
insert into stadiums values (stadiumsSequ.nextval,'KT위즈파크','수원');

//Insert teams tuples
insert into teams values('LG',3,2,1,null);
insert into teams values('SSG',1,4,2,null);
insert into teams values('두산',2,1,1,0.667);
insert into teams values('NC',3,2,3,0.6);
insert into teams values('KT',2,2,4,0.5);

//Insert games tuples
insert into games values(gamesSequ.nextval,'두산','KT','2023-04-21',1,6,10);
insert into games values(gamesSequ.nextval,'KT','SSG','2023-04-20',4,5,8);
insert into games values(gamesSequ.nextval,'LG','NC','2023-04-20',1,9,4);
insert into games values(gamesSequ.nextval,'KT','SSG','2023-04-19',4,5,2);
insert into games values(gamesSequ.nextval,'LG','NC','2023-04-19',1,7,5);
insert into games values(gamesSequ.nextval,'KT','SSG','2023-04-18',4,4,2);
insert into games values(gamesSequ.nextval,'LG','NC','2023-04-18',1,4,6);
insert into games values(gamesSequ.nextval,'LG','두산','2023-04-16',1,5,10);
insert into games values(gamesSequ.nextval,'SSG','NC','2023-04-16',2,5,10);
insert into games values(gamesSequ.nextval,'LG','두산','2023-04-15',1,3,1);
insert into games values(gamesSequ.nextval,'SSG','NC','2023-04-15',2,0,1);

//Show all tuples
Select * from teams;
Select * from games;
Select * from stadiums;

//Set LG’s win rate
UPDATE teams
SET teamWinRate = (
    SELECT wins / (wins + loses) AS teamWinRate
    FROM teams
    WHERE teamName = 'LG' AND wins IS NOT NULL AND loses IS NOT NULL
)
WHERE teamName = 'LG' AND teamWinRate IS NULL;

//Set SSG’s win rate
UPDATE teams
SET teamWinRate = (
    SELECT wins / (wins + loses) AS teamWinRate
    FROM teams
    WHERE teamName = 'SSG' AND wins IS NOT NULL AND loses IS NOT NULL
)
WHERE teamName = 'SSG' AND teamWinRate IS NULL;

//Calculate the number of home games played by each team and sort them in desc order
select homeTeam, count(*)
from games
group by homeTeam
order by count(*) desc;

//Show all the teams that played games on last weekend
(select homeTeam,awayTeam,homeTeamScore,awayTeamScore from games where matchDate='2023-04-15')
union
(select homeTeam,awayTeam,homeTeamScore,awayTeamScore from games where matchDate='2023-04-16');

//Show a pair of teams that use the same stadium
SELECT teamName, sID
from teams t1
where t1.sID in(select t2.sID
               from teams t2
               where t1.sID=t2.sID
               and t1.teamName!=t2.teamName);

//Show stadium name and location of each team
select t.teamName,s.stadiumName,s.location
from teams t
natural join stadiums s;

//Show that table cannot be deleted due to being referenced by a foreign key
drop table stadiums;