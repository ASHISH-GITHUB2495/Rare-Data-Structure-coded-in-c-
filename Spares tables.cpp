#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define ll long long int
#define mod 1000000

//The sparse table for range based quiries ................................................//
const int k = 16;
int st[10][10];
int st2[10][10];
int st3[10][k + 1];

void buildSparseMax(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		st2[i][0] = arr[i];

	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 0; (i + (1 << j) - 1) < n; i++)            //      finding min max from (i) t0 (i+2^j-1)
		{
			st2[i][j] = max(st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1]);

		}
	}
}
void buildSparseMin (int arr[], int n)
{

	for (int i = 0; i < n; i++)
		st[i][0] = arr[i];

	for (int j = 1; (1 << j) <= n ; j++)
	{

		for (int i = 0; (i + (1 << j) - 1) < n; i++)
		{

			if (st[i][j - 1] < st[i + (1 << (j - 1))][j - 1])
				st[i][j] = st[i][j - 1];
			else
				st[i][j] = st[i + (1 << (j - 1))][j - 1];


		}


	}


}
void buildSparseSum(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		st3[i][0] = arr[i];

	for (int j = 1; j <= k ; j++)
	{
		for (int i = 0; i < n - (1 << j) + 1 ; i++)
		{
			st3[i][j] = st3[i][j - 1] + st3[i + (1 << (j - 1))][j - 1];



		}



	}











}
void printSparse()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << st3[i][j] << " ";
		}
		cout << endl;
	}

}
int max_query(int L, int R)
{
	int j = (int)log2(R - L + 1);
	if (st2[L][j] >= st2[R - (1 << j) + 1][j])
		return st2[L][j];
	else
		return st2[R - (1 << j) + 1][j];
}
int min_query(int L, int R)
{
	int j = (int)log2(R - L + 1);

	// Compute minimum of last 2^j elements with first
	// 2^j elements in range.
	// For [2, 10], we compare arr[lookup[0][3]] and
	// arr[lookup[3][3]],
	if (st[L][j] <= st[R - (1 << j) + 1][j])
		return st[L][j];

	else
		return st[R - (1 << j) + 1][j];





}
int sum_query(int L, int R)
{	int sum = 0;
	for (int j = k; j >= 0; j--)
	{
		if ((1 << j) <= (R - L + 1))
		{	sum = sum + st3[L][j];
			L = L + (1 << j);
		}
	}

	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
	clock_t tStart = clock();
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base:: sync_with_stdio(false);
	cin.tie(0);

//////////////////////////////////////start...............

	int n;
	cout << "Enter no. of elements :";
	cin >> n; // input of length of array
	cout << "Enter your elements :" << endl;
	int arr[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

//creating sparse table

	buildSparseMin(arr, n);
	buildSparseMax(arr, n);
	buildSparseSum(arr, n);

	//printSparse();
	cout << ".......ALL RESULTS BY SPARSE TABLE......." << endl << endl;
	cout << "min_query(0, 3) : " << min_query(0, 3) << endl;
	cout << "min_query(4, 7) :" << min_query(4, 4) << endl;
	cout << "max_query(0, 3) :" << max_query(0, 3) << endl;
	cout << "max_query(4, 7) :" << max_query(4, 7) << endl;
	cout << "sum_query(0, 3) :" << sum_query(0, 3) << endl ;
	cout << "sum_query(4, 7) :" << sum_query(4, 7) << endl;











/////////////////////////////end................................... ....
#ifndef ONLINE_JUDGE
	//printf("\nRun Time -> %.10fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
#endif
	return 0;

}

//c v a s selecting text or x for selecting cut
//ctrl+d after selecting text to select same type
//ctrl+shift+d for copy and paste the line below it
//ctrl+del to delete a text
//ctrl+left to jump left of line or vice versa
//ctrl+shift+"/"  to comment whole block and vice versa for undo
//ctrl+"/" for commenting a line
