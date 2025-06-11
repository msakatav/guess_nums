#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"
#include "ft_printf/includes/ft_printf.h"

void ft_generate_answer(int *answer)
{
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i, j, tmp;

    for (i = 9; i > 0; i--)
    {
        j = rand() % (i + 1);
        tmp = digits[i];
        digits[i] = digits[j];
        digits[j] = tmp;
    }
    for (i = 0; i < 3; i++)
        answer[i] = digits[i];
}

int has_duplicates(char *str)
{
    return (str[0] == str[1] || str[0] == str[2] || str[1] == str[2]);
}

int is_valid_input(char *line)
{
    if (!line || line[0] == '\0' || line[1] == '\0' || line[2] == '\0')
        return (0);
    if (line[3] != '\0' && line[3] != '\n')
        return (0);
    if (line[0] < '0' || line[0] > '9' ||
        line[1] < '0' || line[1] > '9' ||
        line[2] < '0' || line[2] > '9')
        return (0);
    if (has_duplicates(line))
        return (0);
    return (1);
}

void str_to_digits(char *str, int *digits)
{
    digits[0] = str[0] - '0';
    digits[1] = str[1] - '0';
    digits[2] = str[2] - '0';
}

void judge_input(int *answer, int *guess, int *match, int *position)
{
    int i, j;

    *match = 0;
    *position = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (guess[i] == answer[j])
            {
                (*match)++;
                if (i == j)
                    (*position)++;
            }
        }
    }
}

void print_title(void)
{
    ft_printf("\n");
    ft_printf("=====================================\n");
    ft_printf("  🎲 数字当てゲーム『ミラクルナンバー』🎲\n");
    ft_printf("=====================================\n");
    ft_printf("ルール: 3桁の異なる数字を5回以内で当てよう！\n");
    ft_printf("ヒント: 数字と位置の一致数が毎回表示されます。\n");
    ft_printf("=====================================\n\n");
}

void print_effect(const char *effect)
{
    ft_printf("%s\n", effect);
    usleep(400000); // 0.4秒演出
}

void print_gameover(int *answer)
{
    const char *faces[] = {
        "(´・ω・｀)", "(；´Д｀)", "(T_T)", "( ﾟдﾟ )", "(ノД`)・゜・。"
    };
    int idx = rand() % 5;
    ft_printf("\n💥 GAME OVER 💥\n");
    print_effect("ドドーン！！");
    ft_printf("残念！正解は %d%d%d でした。\n", answer[0], answer[1], answer[2]);
    ft_printf("%s また挑戦してね！\n", faces[idx]);
}

int main(void)
{
    int answer[3];
    int guess[3];
    char *line;
    int turn = 0;
    int match, position;

    srand(time(NULL));
    print_title();
    ft_generate_answer(answer);

    while (turn < 5)
    {
        ft_printf("🔢 %d 回目のチャレンジ: ", turn + 1);
        line = get_next_line(0);
        if (!is_valid_input(line))
        {
            print_effect("ブッブー！");
            ft_printf("⚠️ 無効な入力です。三桁の異なる数字を入力してください。\n");
            free(line);
            continue;
        }
        str_to_digits(line, guess);
        free(line);

        judge_input(answer, guess, &match, &position);
        if (position == 3)
        {
            print_effect("ピンポンピンポン！！");
            ft_printf("🎉 正解！おめでとうございます！ 🎉\n");
            ft_printf("あなたは %d 回でクリアしました！\n", turn + 1);
            return 0;
        }
        ft_printf("👉 %d つの数字が一致！そのうち %d 個の位置が正しい！\n\n", match, position);
        turn++;
    }
    print_gameover(answer);
    return 0;
}
