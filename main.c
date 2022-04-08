enum MAIN_MENU{END, READ, PRINT, EDIT, WRITE}; // main switch 항목 열거
enum MAIN_MENU main_select;

enum EDIT_MENU{EXIT, PREVIEW, NEXT, INSERT, MODIFY, DELETE, SEARCH}; //edit switch 항목 열거
enum EDIT_MENU edit_select;

#include "student_dll.h"

void read_student();    // 학생 정보 데이터 읽어오기
void write_student();   // 학생 정보 데이터 저장하기
void edit_student();    // 학생 정보 데이터 관리하기
void print_one(STUDENT_t *p); // 개별 학생 정보 출력


char student_fname[20]="student_data.txt";

int main()
{
    int flag=0;

    initialize_student();   // 연결리스트 head 생성

    while(!flag && head!=NULL){
        system("cls");
        puts("====================================");
        puts("\t성적 관리 프로그램");
        puts("====================================");
        puts("\t1. 가져오기");
        puts("\t2. 현황보기");
        puts("\t3. 관리하기");
        puts("\t4. 저장하기");
        puts("\t0. 종료");
        printf("\t>> ");
        scanf_s("%d", &main_select, sizeof(main_select));
        getchar();

        switch(main_select){
        case READ :
            read_student();
            getchar();
            break;
        case PRINT :
            print_student();
            getchar();
            break;
        case EDIT :
            edit_student();
            getchar();
            break;
        case WRITE :
            write_student();
            getchar();
            break;
        case END :
            flag = 1;
            break;
        default :
            puts("\t다시 입력하세요.");
            getchar();
            break;
        }//end of switch
    }//end of while
    return 0;
}

//파일 불러오기
void read_student(){
    STUDENT_t* data=NULL;
    FILE* file=NULL;
    int count=0;
    int flag=0;

    //학생 데이터 입력된 파일 불러오기
    printf("읽어올 파일명을 입력하세요. >> ");
    scanf_s("%s", student_fname, sizeof(student_fname));
    getchar();

    //읽기모드로 파일 열기
    file = fopen(student_fname, "rt");

    //파일이 없는 경우 안내 후 함수종료
    if(file==NULL){
        printf("\t%s 파일을 읽지 못했습니다. \n", student_fname);
        return;
    }

    while(!flag){
        //data 노드 생성
        data = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));

        //파일 열어 데이터 받아오기
        int result = fscanf(file, "%s %d %s %d %d %d %d %d %d %lf %c",
               data->name, &data->id, data->gender, &data->java, &data->android,
               &data->kotlin, &data->react, &data->javascript, &data->total,
               &data->avr, &data->grade);

        //파일 끝까지 읽으면 반복문 해제
        if(result==EOF){
            flag = 1;
            continue;
        }

        //노드에 연결
        append_node(data);
        count++;

        //파일 값 개별 출력
        printf("%s %d %s %d %d %d %d %d %d %.2lf %c\n",
               data->name, data->id, data->gender, data->java, data->android,
               data->kotlin, data->react, data->javascript, data->total,
               data->avr, data->grade);
    }//end of while

    //읽어온 데이터 수 출력
    printf("\t%d개의 데이터를 읽었습니다.", count);
    fclose(file);

    return;
}

// 파일에 성적 저장
void write_student(){
    STUDENT_t* p=head;
    FILE* file=NULL;
    int count=0;

    //쓰기모드로 파일 열기
    file = fopen(student_fname, "wt");

    //파일이 없는 경우 안내 후 함수종료
    if(file==NULL){
        printf("\t%s 파일을 저장하지 못했습니다. \n", student_fname);
        return;
    }

    while(p->next!=NULL){
        p = p->next;

        //파일 열어 데이터 입력
        int result = fprintf(file, "%s %d %s %d %d %d %d %d %d %lf %c \n",
               p->name, p->id, p->gender, p->java, p->android, p->kotlin,
               p->react, p->javascript, p->total, p->avr, p->grade);

        //입력 완료시 반복문 해제
        if(result==EOF){
            printf("\t%s 파일을 저장 도중 문제가 발생하엿습니다. \n", student_fname);
            break;
        }
        count++;
    }//end of while

    //입력한 데이터 수 출력
    printf("\t%d개의 데이터를 저장하였습니다.", count);
    fclose(file);

    return;
}

//이전성적, 다음성적, 성적 추가등록, 성적수정, 성적삭제, 성적검색, 성적정렬
void edit_student(){
    STUDENT_t* data = NULL;
    int flag=0;
    current = head->next; // 데이터 시작 위치 지정(노드위치)

    while(!flag && head!=NULL){
        system("cls");
        puts("====================================");
        puts("\t성적 관리");
        puts("====================================");

        if(current!=NULL){
            print_one(current);
        }

        puts("\t1. 이전 성적");
        puts("\t2. 다음 성적");
        puts("\t3. 성적 추가 입력");
        puts("\t4. 성적 수정");
        puts("\t5. 성적 삭제");
        puts("\t6. 성적 검색");
        puts("\t0. 돌아가기");
        printf("\t>> ");
        scanf_s("%d", &edit_select);
        getchar();

        // 노드가 없을 때 이전, 다음, 수정, 삭제, 검색 기능 제외
        // 등록, 돌아가기만 허용
        if(current==NULL){
            switch(edit_select){
            case PREVIEW :
            case NEXT :
            case MODIFY :
            case DELETE :
            case SEARCH : continue;
            }
        }

        switch(edit_select){
        case PREVIEW :
            if(current->prev!=NULL){
                current = current->prev;
            }
            break;
        case NEXT :
            if(current->next!=NULL){
                current = current->next;
            }
            break;
        case INSERT :
            data = new_student();
            insert_student(data);
            getchar();
            break;
        case MODIFY :
            update_student(current);
            getchar();
            break;
        case DELETE :
            delete_student();
            getchar();
            break;
        case SEARCH :
            data = search_student();
            if(data!=NULL){
                current = data;
            }
            break;
        case EXIT :
            flag = 1;
            break;
        default :
            puts("\t다시 입력하세요.");
            getchar();
            break;
        }//end of switch
    }

    return;
}

// 성적 개별 출력
void print_one(STUDENT_t *p){

    if(p!=NULL){
    printf("%12s [%s] \n", "이름", p->name);
    printf("%12s [%4d] \n", "학번", p->id);
    printf("%12s [%s] \n", "성별", p->gender);
    printf("%12s [%3d] \n", "JAVA", p->java);
    printf("%12s [%3d] \n", "ADROID", p->android);
    printf("%12s [%3d] \n", "KOTLIN", p->kotlin);
    printf("%12s [%3d] \n", "REACT", p->react);
    printf("%12s [%3d] \n", "JAVASCRIPT", p->javascript);
    printf("%12s [%3d] \n", "합계", p->total);
    printf("%12s [%5.2lf] \n", "평균", p->avr);
    printf("%12s [%c] \n", "등급", p->grade);
    puts("====================================\n");
    }

    return;
}
