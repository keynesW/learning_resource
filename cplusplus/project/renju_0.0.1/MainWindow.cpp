/*******************************************************************
 *
 *     File Name    :      MainWindow.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog�� :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 06:12:48 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include "MainWindow.h"
#include <iostream>
using namespace std;

#define CHANGE_CHESS_COLOR(color)  \
    ((color) = (( (color) == COLOR_BLACK ) ? COLOR_WHITE : COLOR_BLACK))

static ChessColor color = COLOR_WHITE;

MainWindow::MainWindow(){}
MainWindow::~MainWindow(){}

bool MainWindow::getWinner()
{
    return chessboard.isWinner(chess_record);
}

void MainWindow::init()
{
    int row,column;
    showMessageBox("please input the boardsize  eg : 10 * 10");
    readChessBoardSize(&row,&column);
}

void MainWindow::update()
{
    int row,column;

#ifdef __linux__
    system("clear");
#elif __WIN32__
    system("cls");
#endif

    CHANGE_CHESS_COLOR(color);

    try{
        readChessPos( color,&row,&column );
    }
    catch(out_of_range e)
    {
        CHANGE_CHESS_COLOR(color);
        string msg("out_of_range please reinput");
        showMessageBox(msg);
    }
    catch(string msg)
    {
        CHANGE_CHESS_COLOR(color);
        showMessageBox(msg);
    }
}

void MainWindow::showChessBoard()
{
/*{{{*/

    const char * ptr_arr[] = {COLOR_BLANK,COLOR_BLACK,COLOR_WHITE,nullptr};
    const char *ptr = ptr_arr[0];

    char str[20] = {'\0'};

    for( int i = 1 ; i <= chessboard.getWidth() ; i ++)
    {
        sprintf(str,"%5d",i);
        cout << str;
    }
    cout << endl;

    for( int i = 1 ; i < chessboard.getHeight(); i ++)
    {
        sprintf(str,"%3d",i);
        cout << str;
        for(int j = 1; j <= chessboard.getWidth() ; j++ )
        {
            ChessColor color = chessboard.chessColor(i-1,j-1);
            if (color == COLOR_BLACK)  
                ptr = ptr_arr[1];
            else
            if(color == COLOR_WHITE)
                ptr =  ptr_arr[2];
            else
                ptr = ptr_arr[0];
            
            sprintf(str,"%s---",ptr);
            cout << str;
        }
        cout << endl;

        sprintf(str,"%3c",' ');
        cout << str;

        for(int j = 1; j <= chessboard.getWidth() ; j++ )
        {
            sprintf(str,"||   ");
            cout << str;
        }
        cout << endl;
    }

    sprintf(str,"%3c",' ');
    cout << str;
    for(int j = 1; j <= chessboard.getWidth() ; j++ )
    {
        sprintf(str,"||---");
        cout << str;
    }
    cout << endl;
    string msg("please input the chesspos you want to pos");
    showMessageBox(msg);
/*}}}*/
}
void MainWindow::showMessageBox(string message)
{
    int boxlen = 1.5*message.size();
    string msgbox(boxlen,'-');
    string becenter(boxlen/6,' ');

    cout << msgbox << endl;
    cout <<  becenter  << message <<  endl;
    cout << msgbox << endl;

}
void MainWindow::showLastResult()
{
    char str[60] = {'\0'};
    string winner("winner is [ " );

    sprintf(str,"white %d : %d  black ",chessboard.getWhiteScore(),\
        chessboard.getBlackScore());

    winner += color;
    winner = winner +" ] " + str;

    string msg(winner);
    showMessageBox(msg);
}
void MainWindow::readChoice(int* choice)
{
    string msg("enter 1 for another round, 0 to quit");
    showMessageBox(msg);

    cin >> (*choice);
}
void MainWindow::readChessPos(ChessColor chessColor, int* row, int* column)
{
    cin >> *row >> *column;
    getchar();
    if( chessboard.isRepeat(*row-1,*column -1) || \
        chessboard.isOutranged(*row -1,*column -1) )
    {
        string message("illegal pos please reinput");
        throw message;
    }
    ChessPos chesspos(*row-1,*column-1);
    Chess chess(chesspos,chessColor);
    chess_record = chess;
    chessboard.addChess(chess);
}

void MainWindow::readChessBoardSize(int* rows, int* columns)
{
    char del;
    cin >> *rows >> del >> *columns;
    chessboard.resize(*columns,*rows); 
    chessboard.init();
} 

