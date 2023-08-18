

class Board{
public:
    
    int board[110];
    int kpos[2];
    int info[4];//2,3は神視点
    int retry[2];

    Board();    
    int push(int move, int move_from);//合法1反則0
    int is_dist_check();//一マス以上開けての王手判定
    int is_close_check();//隣からの王手判定
    int is_check();
    int is_mate();
    int is_lose();
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
private:
};
