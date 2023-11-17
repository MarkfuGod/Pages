#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char prog[500], token[10];
char ch;
int syn, p, m, n, row, sum;
char *rwtab[27] = {
    "main", "if", "then", "while", "do", "static", "int", "double", "struct", "break",
    "else", "long", "switch", "case", "typedef", "char", "return", "const", "float",
    "short", "continue", "for", "void", "sizeof", "ID", "NUM", "default"
  };

void scanner()
{
    for (n = 0; n < 8; ++n)
    {
        token[n] = NULL; // 先将token置空
    }
    ch = prog[p++]; // prog就是程序

    while(ch == ' ')
    {
        ch = prog[p];// 假如是空格 就将相应的字符存给 ch
        ++p;
    }
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        m = 0;
        while((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            token[m++] = ch;
            ch = prog[p++];
        }
        token[m++] = '\0';
        --p;
        syn = 25;
        for (n = 0; n < 27; ++n)
        {
            if (strcmp(token, rwtab[n]) == 0)
            {
                syn = n + 1;
                break;
            }
            else if (strcmp(token, rwtab[26]) == 0)
            {
                syn = 39;
                break;
            }
        }
    }
    else if ((ch >= '0' && ch <= '9'))
    {
        sum = 0;
        while (ch >= '0' && ch <= '9')
        {
            sum = sum * 10 + ch - '0';
            ch = prog[p++];
        }
        --p;
        syn = 26;
        if (sum > 32767)
        {
            syn = -1;
        }
    }
    else switch (ch)
    {
    case '<':
        m = 0;
        token[m++] = ch;
        ch = prog[p++];
        if (ch == '>')
        {
            syn = 34;
            token[m++] = ch;
        }
        else if (ch == '=')
        {
            syn = 35;
            token[m++] = ch;
        }
        else
        {
            syn = 33;
            --p;
        }
        break;
    case '>':
        m = 0;
        token[m++] = ch;
        ch = prog[p++];
        if (ch == '=')
        {
            syn = 37;
            token[m++] = ch;
        }
        else
        {
            syn = 36;
            --p;
        }
        break;
    case ':':
        m = 0;
        token[m++] = ch;
        ch = prog[p++];
        if (ch == '=')
        {
            syn = 32;
            token[m++] = ch;
        }
        else
        {
            syn = 31;
            --p;
        }
        break; 
    case '{':
        syn = 44;
        token[0] = ch;
        break;
    case '}':
        syn = 45;
        token[0] = ch;
        break;
    case '*':
        syn = 29;
        token[0] = ch;
        break;
    case '/':
        syn = 30;
        token[0] = ch;
        break;
    case '+':
        syn = 27;
        token[0] = ch;
        break;
    case '-':
        syn = 28;
        token[0] = ch;
        break;
    case '=':
        syn = 38;
        token[0] = ch;
        break;
    case ';':
        syn = 41;
        token[0] = ch;
        break;
    case '(':
        syn = 42;
        token[0] = ch;
        break;
    case ')':
        syn = 43;
        token[0] = ch;
        break;
    case '"':
        syn = 44;
        token[0] = ch;
        break;
    case '.':
        syn = 45;
        token[0] = ch;
        break;
    case '\'':
        syn = 46;
        token[0] = ch;
        break;
    case '!':
        syn = 47;
        token[0] = ch;
        break;
    case '[':
        syn = 48;
        token[0] = ch;
        break;
    case ']':
        syn = 49;
        token[0] = ch;
        break;
    case '#':
        syn = 0;
        token[0] = ch;
        break;
    case '\n':
        syn = -2;
        break;
    default:
        syn = -1;
        break;
    }
}

int main()
{
    p = 0;
    row  = 1;
    cout << "请输入程序片段:" << endl;

    do 
    {
        cin.get(ch);
        prog[p++] = ch;
    } while (ch != '#');
    
    p = 0;
    
    do
    {
        scanner();
        switch (syn)
        {
        case 26:
            cout << '(' << syn << "," << sum << ")" << endl;
            break;
        case -1:
            cout << "错误发生在第" << row << "行" <<"!" << endl;
            break;
        case -2:
            //++row;
            cout << "这里是换行，第" << row ++ << endl;
            break;
        default:
            cout << "(" << syn << "," << token << ")" << endl;
            break;
        }
    } while (syn != 0);
}
