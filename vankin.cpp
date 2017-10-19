#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int n;
    int k;
    int test;
    FILE* fp;
    fp = fopen("input.txt", "rb");
    fscanf(fp, "%d", &n);
    printf("num = %d\n", n);
    int grid[n][n];

    for(int i=0;;i++){
        for(int j=0;;j++){
            if(fscanf(fp, "%d", &test) == -1)
                goto end;
            grid[i][j]=test;
            printf("grid[%d][%d] = %d\n", i, j, grid[i][j]);
            if((k=fgetc(fp)) == '\n')
                break;
            }
        }
    end:
        printf("All Done\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << grid[i][j] << " ";
			if (j == n - 1)
				std::cout << std::endl;
		}
	}
	std::cout << "---------------------------" << "\n";
	int mostExpensive = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int costs[n][n];
			costs[x][y] = grid[x][y];
			/*for (int i = 0; i < x - 1; i++) {
				for (int j = 0; j < y - 1; j++) {
					tc[i][j]
				}
			}*/
			int i, j;
			for (i = x+1; i <= n - 1; i++)
				costs[i][0] = costs[i - 1][0] + grid[i][0];

			for (j = y+1; j <= n - 1; j++)
				costs[0][j] = costs[0][j - 1] + grid[0][j];

			for (i = x+1; i <= n - 1; i++)
				for (j = y+1; j <= n - 1; j++)
					costs[i][j] = max(costs[i - 1][j], costs[i][j - 1]) + grid[i][j];

			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					std::cout << costs[i][j] << " ";
					if (j == n - 1)
						std::cout << std::endl;
				}
			}
			
			int totals[2 * n];
			for (int i = 0; i < n; i++)
				totals[i] = costs[i][n - 1];
			for (int j = 0; j < n; j++)
				totals[n+j] = costs[n-1][j];
			//PRINT THE ARRAY
			for (int i = 0; i < 2 * n; i++)
				std::cout << totals[i] << " ";
			std::cout << std::endl;
			//sort the array
			bool swapped = true;
			int k = 0;
			int tmp;
			while (swapped) {
				swapped = false;
				k++;
				for (int i = 0; i < 2*n - k; i++) {
					if (totals[i] > totals[i + 1]) {
						tmp = totals[i];
						totals[i] = totals[i + 1];
						totals[i + 1] = tmp;
						swapped = true;
					}
				}
			}//end sort
			//PRINT SORTED ARRAY
			for (int i = 0; i < 2 * n; i++)
				std::cout << totals[i] << " ";
			std::cout << std::endl;

			for (int i = 0; i < 2 * n; i++) {
				if (totals[i] > mostExpensive)
					mostExpensive = totals[i];
			}

		}//end y
	}//end x
	std::cout << "Max: " << mostExpensive << std::endl;
    FILE* fd = fopen("output.txt", "w");
    fprintf(fd, "%d", mostExpensive);
    fclose(fd);
    return 0;
 
}
