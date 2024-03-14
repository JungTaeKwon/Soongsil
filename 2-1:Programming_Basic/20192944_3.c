#include <stdio.h>
#include <string.h>
char nameCol[21][10] = { "이름" ,"Sophia","Olivia","Riley","Emma","Ava","Isabella","Aria","Amelia","Mia","Liam","Noah","Jackson","Aiden","Elijah","Grayson","Lucas","Oliver","Caden","Mateo","David" };
char numCol[21][10] = { "학번","20220001","20220010","20220002","20220015","20220009","20220014","20220020","20220005","20220016","20220008","20220012","20220004","20220018","20220017","20220003","20220013","20220007","20220019","20220011","20220006" };
char gradeCol[21][10] = { "점수", "98","96","88","77","82","93","84","79","90","80","89","99","78","83","92","71","72","68","96","76" };

void ViewList()
{
        printf("%-12s %-12s %-3s\n", nameCol[0], numCol[0], gradeCol[0]);
    for (int i = 1; i < 21; i++)
    {
        printf("%-10s %-10s %-3s\n", nameCol[i], numCol[i], gradeCol[i]);
    }
    printf("\n");
}

void AscendingNamePrint()
{
    for (int i = 1; i < 20; i++)
    {
        for (int j = i + 1; j < 21; j++)
        {
            if (strcmp(nameCol[i], nameCol[j])>0)
            {
                char temp1[10];
                char temp2[10];
                char temp3[10];

                strcpy(temp1, nameCol[j]);
                strcpy(nameCol[j], nameCol[i]);
                strcpy(nameCol[i], temp1);

                strcpy(temp2, numCol[j]);
                strcpy(numCol[j], numCol[i]);
                strcpy(numCol[i], temp2);

                strcpy(temp3, gradeCol[j]);
                strcpy(gradeCol[j], gradeCol[i]);
                strcpy(gradeCol[i], temp3);
            }
        }
    }
    ViewList();
}

void AscendingNumPrint()
{
    for (int i = 1; i < 20; i++)
    {
        for (int j = i + 1; j < 21; j++)
        {
            if (strcmp(numCol[i], numCol[j]) > 0)
            {
                char temp1[10];
                char temp2[10];
                char temp3[10];

                strcpy(temp1, nameCol[j]);
                strcpy(nameCol[j], nameCol[i]);
                strcpy(nameCol[i], temp1);

                strcpy(temp2, numCol[j]);
                strcpy(numCol[j], numCol[i]);
                strcpy(numCol[i], temp2);
                
                strcpy(temp3, gradeCol[j]);
                strcpy(gradeCol[j], gradeCol[i]);
                strcpy(gradeCol[i], temp3);
            }
        }
    }
    ViewList();
}

void DescendingGradePrint()
{
    for (int i = 1; i < 20; i++)
    {
        for (int j = i + 1; j < 21; j++)
        {
            if (strcmp(gradeCol[i], gradeCol[j]) < 0)
            {
                char temp1[10];
                char temp2[10];
                char temp3[10];

                strcpy(temp1, nameCol[j]);
                strcpy(nameCol[j], nameCol[i]);
                strcpy(nameCol[i], temp1);

                strcpy(temp2, numCol[j]);
                strcpy(numCol[j], numCol[i]);
                strcpy(numCol[i], temp2);

                strcpy(temp3, gradeCol[j]);
                strcpy(gradeCol[j], gradeCol[i]);
                strcpy(gradeCol[i], temp3);
            }
        }
    }
    ViewList();
}

void SearchName()
{
    char name[10];
    printf("이름을 입력하세요 : ");
    scanf("%s", name);
    printf("\n");
    printf("%-12s %-12s %-3s\n", nameCol[0], numCol[0], gradeCol[0]);
    for (int i = 1; i < 21; i++)
    {
        if (!strcmp(name, nameCol[i]))
        {
            printf("%-10s %-10s %-3s\n\n", nameCol[i], numCol[i], gradeCol[i]);
        }
    }
}

int main(void)
{
    int select;

    while (1)
    {
        printf("1. 이름 오름차순 출력\t 2. 학번 오름차순 출력\n");
        printf("3. 점수 내림차순 출력\t 4. 이름 검색\n");
        printf("5. 종료\n\n");
        printf("번호를 선택하세요 : ");
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            AscendingNamePrint();
            break;
        case 2:
            AscendingNumPrint();
            break;
        case 3:
            DescendingGradePrint();
            break;
        case 4:
            SearchName();
            break;
        case 5:
            return 0;
        default:
            break;
        }
    }
    return 0;
}