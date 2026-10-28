#include <stdio.h>
#define N 10

struct Person {
    char name[30];
    float paid, bal;
};

int main() {
    struct Person p[N];
    float g[N][N] = {0}, b[N], total, share, amt;
    int n, ch, i, j, x, d, c, order[N], temp;

    printf("\n====================================\n");
    printf("       SPLITSMART\n");
    printf("  GROUP EXPENSE MANAGER\n");
    printf("====================================\n");

    printf("\nHow many friends are sharing expenses? (2-10): ");
    scanf("%d", &n);

    if (n < 2 || n > N) {
        printf("Please enter between 2 and 10 friends.\n");
        return 0;
    }

    printf("\n=== ENTER FRIEND DETAILS ===\n");

    for (i = 0; i < n; i++) {
        printf("Enter name of Friend %d: ", i + 1);
        scanf("%29s", p[i].name);
        p[i].paid = 0;
    }

    printf("\nFriends added successfully!\n");

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View Balances\n");
        printf("3. Sort Balances (Bubble Sort)\n");
        printf("4. Settle Expenses (Graph)\n");
        printf("5. Exit\n");
        printf("Choose an option (1-5): ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("\n========== ADD EXPENSE ==========\n");
            printf("Who paid? Select a friend:\n");

            for (i = 0; i < n; i++)
                printf("%d. %s\n", i + 1, p[i].name);

            printf("Enter friend number (1-%d): ", n);
            scanf("%d", &x);

            if (x < 1 || x > n) {
                printf("Invalid friend number!\n");
                continue;
            }

            printf("Selected friend: %s\n", p[x - 1].name);
            printf("Enter amount paid (Rs.): ");
            scanf("%f", &amt);

            if (amt <= 0) {
                printf("Amount must be greater than zero!\n");
                continue;
            }

            p[x - 1].paid += amt;
            printf("\nExpense added successfully!\n");
            printf("%s paid Rs. %.2f\n", p[x - 1].name, amt);
        }

        else if (ch >= 2 && ch <= 4) {
            total = 0;

            for (i = 0; i < n; i++)
                total += p[i].paid;

            share = total / n;

            for (i = 0; i < n; i++) {
                p[i].bal = p[i].paid - share;
                b[i] = p[i].bal;
                order[i] = i;
            }

            if (ch == 2) {
                printf("\n========== EXPENSE SUMMARY ==========\n");
                printf("Total group expense: Rs. %.2f\n", total);
                printf("Equal share per friend: Rs. %.2f\n\n", share);

                printf("%-15s %-12s %s\n", "FRIEND", "PAID", "STATUS");
                printf("-----------------------------------------------\n");

                for (i = 0; i < n; i++) {
                    printf("%-15s Rs. %-9.2f ", p[i].name, p[i].paid);

                    if (p[i].bal > 0.01)
                        printf("Receives Rs. %.2f\n", p[i].bal);
                    else if (p[i].bal < -0.01)
                        printf("Owes Rs. %.2f\n", -p[i].bal);
                    else
                        printf("Settled\n");
                }
            }

            else if (ch == 3) {
                printf("\n========== SORTED BALANCES ==========\n");
                printf("Using Bubble Sort: highest receiver first\n\n");

                for (i = 0; i < n - 1; i++)
                    for (j = 0; j < n - i - 1; j++)
                        if (p[order[j]].bal < p[order[j + 1]].bal) {
                            temp = order[j];
                            order[j] = order[j + 1];
                            order[j + 1] = temp;
                        }

                for (i = 0; i < n; i++) {
                    x = order[i];
                    printf("%-15s Balance: Rs. %.2f\n",
                           p[x].name, p[x].bal);
                }
            }

            else if (ch == 4) {
                printf("\n========== SMART SETTLEMENT ==========\n");
                printf("Using Greedy Algorithm and Graph\n\n");

                for (i = 0; i < n; i++)
                    for (j = 0; j < n; j++)
                        g[i][j] = 0;

                for (i = 0; i < n; i++)
                    if (b[i] > -0.01 && b[i] < 0.01)
                        b[i] = 0;

                while (1) {
                    d = c = -1;

                    for (i = 0; i < n; i++) {
                        if (b[i] < -0.01 &&
                            (d == -1 || b[i] < b[d]))
                            d = i;

                        if (b[i] > 0.01 &&
                            (c == -1 || b[i] > b[c]))
                            c = i;
                    }

                    if (d == -1 || c == -1)
                        break;

                    amt = (-b[d] < b[c]) ? -b[d] : b[c];

                    g[d][c] += amt;
                    b[d] += amt;
                    b[c] -= amt;

                    if (b[d] > -0.01) b[d] = 0;
                    if (b[c] < 0.01) b[c] = 0;
                }

                printf("Suggested payments:\n");
                temp = 0;

                for (i = 0; i < n; i++)
                    for (j = 0; j < n; j++)
                        if (g[i][j] > 0.01) {
                            printf("%s pays %s: Rs. %.2f\n",
                                   p[i].name, p[j].name, g[i][j]);
                            temp++;
                        }

                if (temp == 0)
                    printf("No payments needed. All settled!\n");

                printf("\nSettlement Graph (Adjacency Matrix):\n");
                printf("%12s", "");

                for (i = 0; i < n; i++)
                    printf("%10s", p[i].name);

                printf("\n");

                for (i = 0; i < n; i++) {
                    printf("%12s", p[i].name);

                    for (j = 0; j < n; j++)
                        printf("%10.2f", g[i][j]);

                    printf("\n");
                }
            }
        }

        else if (ch == 5) {
            printf("\nThank you for using SplitSmart!\n");
        }

        else {
            printf("\nInvalid option! Please choose 1-5.\n");
        }

    } while (ch != 5);

    return 0;
}