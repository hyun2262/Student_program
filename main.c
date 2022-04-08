enum MAIN_MENU{END, READ, PRINT, EDIT, WRITE}; // main switch �׸� ����
enum MAIN_MENU main_select;

enum EDIT_MENU{EXIT, PREVIEW, NEXT, INSERT, MODIFY, DELETE, SEARCH}; //edit switch �׸� ����
enum EDIT_MENU edit_select;

#include "student_dll.h"

void read_student();    // �л� ���� ������ �о����
void write_student();   // �л� ���� ������ �����ϱ�
void edit_student();    // �л� ���� ������ �����ϱ�
void print_one(STUDENT_t *p); // ���� �л� ���� ���


char student_fname[20]="student_data.txt";

int main()
{
    int flag=0;

    initialize_student();   // ���Ḯ��Ʈ head ����

    while(!flag && head!=NULL){
        system("cls");
        puts("====================================");
        puts("\t���� ���� ���α׷�");
        puts("====================================");
        puts("\t1. ��������");
        puts("\t2. ��Ȳ����");
        puts("\t3. �����ϱ�");
        puts("\t4. �����ϱ�");
        puts("\t0. ����");
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
            puts("\t�ٽ� �Է��ϼ���.");
            getchar();
            break;
        }//end of switch
    }//end of while
    return 0;
}

//���� �ҷ�����
void read_student(){
    STUDENT_t* data=NULL;
    FILE* file=NULL;
    int count=0;
    int flag=0;

    //�л� ������ �Էµ� ���� �ҷ�����
    printf("�о�� ���ϸ��� �Է��ϼ���. >> ");
    scanf_s("%s", student_fname, sizeof(student_fname));
    getchar();

    //�б���� ���� ����
    file = fopen(student_fname, "rt");

    //������ ���� ��� �ȳ� �� �Լ�����
    if(file==NULL){
        printf("\t%s ������ ���� ���߽��ϴ�. \n", student_fname);
        return;
    }

    while(!flag){
        //data ��� ����
        data = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));

        //���� ���� ������ �޾ƿ���
        int result = fscanf(file, "%s %d %s %d %d %d %d %d %d %lf %c",
               data->name, &data->id, data->gender, &data->java, &data->android,
               &data->kotlin, &data->react, &data->javascript, &data->total,
               &data->avr, &data->grade);

        //���� ������ ������ �ݺ��� ����
        if(result==EOF){
            flag = 1;
            continue;
        }

        //��忡 ����
        append_node(data);
        count++;

        //���� �� ���� ���
        printf("%s %d %s %d %d %d %d %d %d %.2lf %c\n",
               data->name, data->id, data->gender, data->java, data->android,
               data->kotlin, data->react, data->javascript, data->total,
               data->avr, data->grade);
    }//end of while

    //�о�� ������ �� ���
    printf("\t%d���� �����͸� �о����ϴ�.", count);
    fclose(file);

    return;
}

// ���Ͽ� ���� ����
void write_student(){
    STUDENT_t* p=head;
    FILE* file=NULL;
    int count=0;

    //������� ���� ����
    file = fopen(student_fname, "wt");

    //������ ���� ��� �ȳ� �� �Լ�����
    if(file==NULL){
        printf("\t%s ������ �������� ���߽��ϴ�. \n", student_fname);
        return;
    }

    while(p->next!=NULL){
        p = p->next;

        //���� ���� ������ �Է�
        int result = fprintf(file, "%s %d %s %d %d %d %d %d %d %lf %c \n",
               p->name, p->id, p->gender, p->java, p->android, p->kotlin,
               p->react, p->javascript, p->total, p->avr, p->grade);

        //�Է� �Ϸ�� �ݺ��� ����
        if(result==EOF){
            printf("\t%s ������ ���� ���� ������ �߻��Ͽ����ϴ�. \n", student_fname);
            break;
        }
        count++;
    }//end of while

    //�Է��� ������ �� ���
    printf("\t%d���� �����͸� �����Ͽ����ϴ�.", count);
    fclose(file);

    return;
}

//��������, ��������, ���� �߰����, ��������, ��������, �����˻�, ��������
void edit_student(){
    STUDENT_t* data = NULL;
    int flag=0;
    current = head->next; // ������ ���� ��ġ ����(�����ġ)

    while(!flag && head!=NULL){
        system("cls");
        puts("====================================");
        puts("\t���� ����");
        puts("====================================");

        if(current!=NULL){
            print_one(current);
        }

        puts("\t1. ���� ����");
        puts("\t2. ���� ����");
        puts("\t3. ���� �߰� �Է�");
        puts("\t4. ���� ����");
        puts("\t5. ���� ����");
        puts("\t6. ���� �˻�");
        puts("\t0. ���ư���");
        printf("\t>> ");
        scanf_s("%d", &edit_select);
        getchar();

        // ��尡 ���� �� ����, ����, ����, ����, �˻� ��� ����
        // ���, ���ư��⸸ ���
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
            puts("\t�ٽ� �Է��ϼ���.");
            getchar();
            break;
        }//end of switch
    }

    return;
}

// ���� ���� ���
void print_one(STUDENT_t *p){

    if(p!=NULL){
    printf("%12s [%s] \n", "�̸�", p->name);
    printf("%12s [%4d] \n", "�й�", p->id);
    printf("%12s [%s] \n", "����", p->gender);
    printf("%12s [%3d] \n", "JAVA", p->java);
    printf("%12s [%3d] \n", "ADROID", p->android);
    printf("%12s [%3d] \n", "KOTLIN", p->kotlin);
    printf("%12s [%3d] \n", "REACT", p->react);
    printf("%12s [%3d] \n", "JAVASCRIPT", p->javascript);
    printf("%12s [%3d] \n", "�հ�", p->total);
    printf("%12s [%5.2lf] \n", "���", p->avr);
    printf("%12s [%c] \n", "���", p->grade);
    puts("====================================\n");
    }

    return;
}
