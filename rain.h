#ifndef _RAIN_H_
#define _RAIN_H_
#define MAX 50

class Node {
  public:
    char word[MAX];
    int row, col;
    Node *nextNode;
};

Node *createNode();
const char *randomWord();
void *thread_word(void *none);
void rainGame();
void draw(int row, int col, const char *str);
void addWord(const char *word, int col);

/*class Rain {
  public:
    int score = 0;
    char score_str[MAX] = "";
    int hp = 5;
    char hp_str[2] = "";
    Node *fnode = 0;

    Node *createNode();

    const char *randomWord();
    void *thread_word(void *);
    void game();
    void draw(int row, int col, const char *str);
    void addWord(const char *word, int col);
};*/

#endif
