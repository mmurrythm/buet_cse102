#include<stdio.h>

#define ROLL 2505139
#define PROFILE ((((ROLL - 1) * 37) / 370) * 19 + ((ROLL * 11 + 7) % 19)) / 19
#define ANAGRAM_INDEX (PROFILE % 3)
#define CIPHER_INDEX  ((PROFILE / 3) % 3)
#define GUESS_INDEX   ((PROFILE / 9) % 3)
#define SCRAMBLE_OFFSET(L) ((PROFILE % ((L) - 1)) + 1)
#define SHIFT         ((PROFILE % 23) + 3) // cipher shift value

const char *anagrams[3] = {"listen", "earth", "binary"};
const char *ciphers[3] = {"there is a secret code", "attack at dawn", "meet me at the park"};
const char *guesses[3] = {"program", "network", "science"};
int L;
int score =0, completed_challenges=0;

int show_menu()
{
    printf("+======================================+\n|               GAME WORLD             |\n|        Words , Ciphers , Victory     |\n+======================================+\n");
    printf("1. Start Game\n2. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    scanf("%*c"); // \n is not taken as input
    return choice;
}
int stringlength(const char *str);
int stringlength(const char *str)
{
    int L = 0, i = 0;
    while (str[L] != '\0')
    {
        L++;
    }
    return L;
}

int stringCompare(const char *str1, const char *str2);
int stringCompare(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
        i++;
    }
    return (str1[i] == str2[i]); // Return 1 if both strings end at the same time, else 0
}

int scrambled_word(char *str);
int scrambled_word(char *str)
{
    int i=0, j=0;
    char str_intermediate[10];
    while(anagrams[ANAGRAM_INDEX][i]!='\0')
    {
        str_intermediate[i]=anagrams[ANAGRAM_INDEX][i];
        i++;
    }
    str_intermediate[i]='\0';
    int anagram_L = stringlength(str_intermediate);
    while(j<anagram_L)
    {
        str[j] = str_intermediate[(j+SCRAMBLE_OFFSET(anagram_L)) % anagram_L];
        printf("%c", str[j]);
        j++;;
    }
    str[anagram_L]= '\0';
    anagram_L = stringlength(str);
    return *str;
}

int anagram();
int anagram()
{
    printf("Starting Anagram Challenge ..\n");
    printf("Scrambled word : ");
    char str[20];
    scrambled_word(str);
    L = stringlength(str);

    char input_word[20];
    int attempts = 0;
    while(attempts < 3)
    {
        int i = 0;

        printf("\nYour guess: ");

        fgets(input_word, sizeof(input_word), stdin);
        while(input_word[i] != '\0')
        {
            if(input_word[i] == '\n')
            {
                input_word[i] = '\0'; // from earth\n\0 to earth\0
                break;
            }
            i++;
        }
//        printf("\ndebug inp: [%s]\n", input_word);
        if(stringCompare(input_word,anagrams[ANAGRAM_INDEX])==1)
        {
            printf("Correct ! You solved it in %d attempt ( s ) .", attempts + 1);

            score += 10;
            score += (2 - attempts) * 10;
            completed_challenges++;
            break;
        }
        else
        {
            printf("Incorrect ! Try again .");
        }
        attempts++;
    }
    return 0;
}

int cipher_encrypt(char *str);
int cipher_encrypt(char *str)
{
    printf("\nEncrypted phrase : ");
    int i=0, j=0;
    int  cipher_L = stringlength(ciphers[CIPHER_INDEX]);

    while(i<cipher_L)
    {
        str[j]=ciphers[CIPHER_INDEX][i];
        if(str[j] != ' ')
        {
            str[j] = ((str[j] - 'a' + SHIFT) % 26) + 'a';
        }
        i++;
        j++;
    }
    str[cipher_L]='\0';
    puts(str);
    return 0;
}

int cipher_decrypt(char *str);
int cipher_decrypt(char *str)
{
    int i=0;
    int  cipher_L = stringlength(str);
    while(i<cipher_L)
    {
        if(str[i]!= ' ')
        {
            str[i] = ((str[i] - 'a' - SHIFT + 26) % 26) + 'a';
        }
        else
        {
            str[i] = ' ';

        }
        i++;
    }
    str[cipher_L]='\0';
    return 0;
}

int caesar_cipher();
int caesar_cipher()
{
    printf("\nStarting Caesar Cipher Challenge ( Shift : %d ) ...", SHIFT);
    char encrypted_phrase[100];
    char decrypted_phrase[100];
    cipher_encrypt(encrypted_phrase);
    int cipher_L = stringlength(encrypted_phrase);
//  printf("\nDEBUG encrypted: [%s]", encrypted_phrase);
//  printf("\nDEBUG cipher_L: %d\n", cipher_L);
    int i = 0;

    while(i < cipher_L)
    {
        decrypted_phrase[i] = encrypted_phrase[i];
        i++;
    }
    decrypted_phrase[i] = '\0';
//  printf("DEBUG before decrypt: [%s]\n", decrypted_phrase);
//  printf("DEBUG decrypted L: %d\n",
    cipher_decrypt(decrypted_phrase);
    int attempts=0;
    while(attempts<3)
    {
        int i=0;
        printf("Your guess : ");
        char input_phrase[100];
        fgets(input_phrase, sizeof(input_phrase), stdin);
        while(input_phrase[i] != '\0')
        {
            if(input_phrase[i] == '\n')
            {
                input_phrase[i] = '\0';
                break;
            }
            i++;
        }
        if(stringCompare(input_phrase,decrypted_phrase))
        {
            printf("Correct ! You decrypted it in %d attempt ( s ) .", attempts + 1);
            score += 10;
            score += (2 - attempts) * 10;
            completed_challenges++;
            break;
        }
        else
        {
            printf("Incorrect ! Try again .");
        }
        attempts++;
        scanf("%*c");
    }
    return 0;
}

int isSubstring(char *str);
int isSubstring(char *str)
{
    int guess_L=stringlength(guesses[GUESS_INDEX]);
    int input_L=stringlength(str);
    int i = 0, j= 0;
    if(input_L> guess_L)
    {
        return 0;
    }
    while(i<=guess_L-input_L)
    {
        while(j < input_L && guesses[GUESS_INDEX][i+j] == str[j])
        {
            j++;
        }
        i++;
    }
    return input_L == j;
}
int word_guess();
int word_guess()
{
    printf("\nStarting Word Guess Challenge ...");
    printf("\nHint : ");
    int i= 0,correct= 0,choice, substr_utility = 0, length_utility =0;
    int guess_L = stringlength(guesses[GUESS_INDEX]);
    while(i < guess_L)
    {
        if(i <3)
        {
            printf("%c", guesses[GUESS_INDEX][i]);
        }
        else
        {
            printf("_");
        }
        i++;
    }
    printf("\nSelect an option : 1. Write Answer 2. Check Substring 3. Check Length\n");
    while(correct == 0 )
    {
        scanf("%d",&choice);
        scanf("%*c");
        switch(choice)
        {
        case 1:
        {
            int attempts = 0;
            while(attempts<3 && correct ==0)
            {
                int i = 0;
                char input_word[10];

                printf("\nEnter your guess : ");

                fgets(input_word,sizeof(input_word), stdin);

                while(input_word[i] != '\0')
                {
                    if(input_word[i] == '\n')
                    {
                        input_word[i] = '\0';  // from earth\n\0 to earth\0
                        break;
                    }
                    i++;
                }
                if(stringCompare(input_word,guesses[GUESS_INDEX]))
                {
                    printf("Correct!");
                    correct=1;
                    score += 10;
                    score += (2 - attempts) * 10;
                    completed_challenges++;
                    break;
                }
                else
                {
                    printf("\nIncorrect ! Try again .");
                }
                attempts++;
            }
            break;
        }

        case 2:
            if( substr_utility == 0)
            {
                char substring[10];
                printf("Enter substring :");
                scanf("%s",substring);
                if(isSubstring(substring))
                {
                    printf("Yes\n");
                }
                else
                {
                    printf("No\n");
                }
                substr_utility = 1;
            }
            else
            {
                printf("Error : Utility function already used .\n");
            }
            break;
        case 3:
            if(length_utility == 0)
            {
                int length;
                printf("Enter length : ");
                scanf("%d",&length);
                if( length == stringlength(guesses[GUESS_INDEX]))
                {
                    printf("Yes\n");
                }
                else
                {
                    printf("No\n");
                }
                length_utility = 1;
                break;
            }
            else
            {
                printf("Error : Utility function already used \n");
            }
            break;
        default:
            printf("Invalid Choice.\n");
            break;
        }
    }
    return 0;
}

int main()
{
    int choice;
    choice = show_menu();
    switch(choice)
    {
    case 1:
        printf("Starting the game...\n");
        anagram();
        caesar_cipher();
        word_guess();
        if(completed_challenges == 3)
        {
            score += 5;
        }
        printf("Game Over! \nYour total score : %d points", score);
        break;
    case 2:
        printf("Exiting the game...\n");
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }
    return 0;
}
