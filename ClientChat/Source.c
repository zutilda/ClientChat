#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
    system("chcp 1251 > null");
    LPSTR lpstrPipeName = L"\\\\.\\pipe\\MyPipe"; // ��� ������ (����� ��, ��� � �� ������)
    HANDLE hNamePipe; // ���������� �����
    BOOL flag_otvet = TRUE;
    char message[SIZE_BUFFER]; // ������ ���������
    DWORD size_buffer = SIZE_BUFFER; // ������ ������ ��� ������
    DWORD actual_written; // ������� �� ����� ���� ���� �������� ����
    LPWSTR buffer = &message; // ��������� ���������, �������� ������� ������������ � �����
    DWORD actual_readen; // ������� �� ����� ���� ���� ��������� ����
    BOOL isSuccess;
    BOOL SuccessRead;
    while (TRUE)
    {

        hNamePipe = CreateFile( // ��������� �����. �� �������� � ��������� �����
            lpstrPipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );
        DWORD dwMode = PIPE_READMODE_MESSAGE; //������������ � ����� ������ � �������
        BOOL isSuccess = SetNamedPipeHandleState( //�������� ������ ��� ���
            hNamePipe,
            &dwMode,
            NULL,
            NULL
        );
        if (!isSuccess)
        {
            printf("\n������ �� ��������\n");
            flag_otvet = TRUE;
        }
        else
        {
             //������ ���������
            LPSTR message = calloc(SIZE_BUFFER, sizeof(CHAR));
            if (flag_otvet)
            {
                printf("���������: ");
                gets(message);
                WriteFile(hNamePipe, message, SIZE_BUFFER, NULL, NULL);
                flag_otvet = FALSE;
            }
            free(message);

            message = calloc(SIZE_BUFFER, sizeof(CHAR));
            if (ReadFile(hNamePipe, message, SIZE_BUFFER, NULL, NULL))
            {
                printf("������: %s\n", message);
                flag_otvet = TRUE;
            }
            free(message);


            //if (flag_otvet)
            //{
            //    printf("\n������� ����� ��� �������:\n");
            //    gets(message);
            //    buffer = &message;
            //    WriteFile(hNamePipe, buffer, size_buffer, &actual_written, NULL); // ������ � �����
            //    flag_otvet = FALSE;

            //}
            ////������ � ��������
            //SuccessRead = ReadFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
            //if (SuccessRead)
            //{
            //    printf("\n�����:\n");
            //    printf(buffer);
            //    printf("\n");
            //    flag_otvet = TRUE;
            //}
        }


        Sleep(100);
        CloseHandle(hNamePipe);
    }


}