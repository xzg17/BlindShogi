

class Board{
public:
    Board();
    int board[110];
    int kpos[2];
    int info[4];//2,3は神視点
    int retry[2];
    
    int push(int move, int move_from);//合法1反則0
    int is_dist_check();//一マス以上開けての王手判定
    int is_close_check();//隣からの王手判定
    int is_end();
    int is_check();
    int board[62];//0~24盤25~34持駒35,36反則37手数38王手の有無39遠距離王手の有無40近距離王手の有無
    int kpos[2];
    int end;
    int set(int *in_board);
    void direction_N1(int *moves1, int pos);
    void direction_S1(int *moves1, int pos);
    void direction_EW1(int *moves1, int pos);
    void direction_NEW1(int *moves1, int pos);
    void direction_SEW1(int *moves1, int pos);
    void direction_PR1(int *moves1, int pos);
    void direction_PB1(int *moves1, int pos);

    void direction_N2(int *moves2, int pos);
    void direction_EW2(int *moves2, int pos);
    void direction_NEW2(int *moves2, int pos);
    void direction_PR2(int *moves2, int pos);
    void direction_PB2(int *moves2, int pos);

    void direction_S3(int *moves3, int pos);
    void direction_SEW3(int *moves3, int pos);
    void direction_PR3(int *moves3, int pos);
    void direction_PB3(int *moves3, int pos);
    
    int pseudo_moves1(int *moves1);
    int pseudo_moves2(int *moves2);
    int pseudo_moves3(int *moves3);
    int pseudo_moves4(int *moves4);
    //以下使うか怪しいもの
    int moves1[200];//成でない「指す」手。移動先*方向=25*8=200
    int moves2[25];//可成域への成る手。移動先*方向=5*5=25(+200)
    int moves3[60];//非可成域への成る手。移動先*方向=20*3=(+225)
    int moves4[125];//打つ手。移動先*駒種=25*5=125(+285)
private:
};
