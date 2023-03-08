#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

//Task 1 - Min SPan Tree
vector<vector<int> > MinSpanTree(vector<vector<int>>& Matrix) // PRIM
{
	int size = Matrix.size();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (Matrix[i][j] == 0){
				Matrix[i][j] = INT_MAX;
			}
		}
	}
	vector<vector<int> > Ostov(size, vector<int>(size, 0));
	vector<bool> visited(size, false);
	visited[0] = true;
	int no_edge = 0, mincost = 0;
	while (no_edge < size - 1) {
		int min = 10000;
		int a = -1;
		int b = -1;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (Matrix[i][j] < min) {
					if (!((visited[i] == visited[j]))) {
						min = Matrix[i][j];
						a = i; b = j;
					}
				}
			}
		}
		if (a != -1 && b != -1) {

			no_edge++;
			mincost = mincost + min;
			visited[b] = true;
			visited[a] = true;
			Ostov[a][b] = Matrix[a][b];
			Ostov[b][a] = Matrix[a][b];
		}
	}
	return Ostov;
}



//DFS - Task 2
void DFS_f( vector<vector<int>>  Matrix, int start, int size, vector<bool>& visited, vector<int>& result) {
	visited[start] = true;
	result.push_back(start);
	for (int v2 = 0; v2 < size; ++v2)
		if (!visited[v2] && Matrix[start][v2] != 0)
			DFS_f(Matrix, v2, size, visited, result);
}


vector<int> DFS(const vector<vector<int>> Matrix, int start) {
	int size = Matrix.size();
	vector<bool> visited(size, 0);
	vector<int> result;
	DFS_f(Matrix, start, size, visited, result);
	return result;
}


vector<int> MST_DFS(vector<vector<int>>& Matrix, int start) {
	int size = Matrix.size();
	vector<vector<int> > MST_Matrix = MinSpanTree(Matrix);
	vector<bool> visited(size, 0);
	vector<int> result;
	DFS_f(MST_Matrix, start, size, visited, result);
	return result;
}


//Task 3 -  Min Path between i and others
// V^2 + E where V - search for min vertices
vector <int> Dikstra(vector<vector<int>> Matrix, int source) {
	int size = Matrix.size();
	vector<int> dist(size, INT_MAX);
	dist[source] = 0;

	vector<bool> used(size,false);
	
	for (int i = 0; i < size; i++) {
		int v = 0;
		for (int j = 0; j < size; j++)
			if (!used[j] && (v == 0 || dist[j] < dist[v])) v = j;
		if (dist[v] == INT_MAX) break;
		
		used[v] = true;

		for (int j = 0; j < size; j++) { 
			int len = Matrix[v][j];
			if (dist[v] + len < dist[j]) {
				dist[j] = dist[v] + len;
			}
		}
	}
	return dist;
}


//BFS - Task 4
vector<int> BFS(const vector<vector<int> > Matrix, int start) {
	int size = Matrix.size();
	vector<bool> visited(size, 0);
	vector<int> result;
	queue<int> q;
	visited[start] = true;
	q.push(start);
	//result.push_back(start);
	while (!q.empty()){
		int s = q.front();
		q.pop();
		for (int i = 0; i < size; i++){
			if (!visited[i] && Matrix[s][i] != 0){
				visited[i] = true;
				q.push(start);
				result.push_back(i);
			}
		}
	}
	return result;
}

vector<int> CountIncidentalEdges(vector<vector<int>> Matrix, int start) {
	vector<int> res;
	res = BFS(Matrix,start);
	return res;
}



int main()
{
	// матрица смежности
	vector<vector<int> > matrix =
	{
	{ 0, 8, 0, 1, 4, 1, 4, 9, 3, 9 },
	{ 8, 0, 5, 1, 4, 7, 9, 0, 2, 0 },
	{ 0, 5, 0, 9, 6, 0, 5, 6, 0, 6 },
	{ 1, 1, 9, 0, 0, 8, 5, 1, 1, 0 },
	{ 4, 4, 6, 0, 0, 3, 9, 0, 6, 5 },
	{ 1, 7, 0, 8, 3, 0, 1, 1, 4, 7 },
	{ 4, 9, 5, 5, 9, 1, 0, 2, 1, 8 },
	{ 9, 0, 6, 1, 0, 1, 2, 0, 7, 8 },
	{ 3, 2, 0, 1, 6, 4, 1, 7, 0, 7 },
	{ 9, 0, 6, 0, 5, 7, 8, 8, 7, 0 } 
	};

	
	cout << "___Task 1 PrimAlgorithm test___\n";
	vector<vector<int>> result00 = MinSpanTree(matrix);
	/*for (auto el : result00)
		cout << el << "";*/
	
	for (int i = 0; i < 10; i++){
		cout << "\n";
		for (int j = 0; j < 10; j++){
			cout << result00[i][j] << " ";
		}

	}

	cout << "\n___Task 2 DFS test___\n";
	vector<int> result1 = DFS(matrix, 1);
	for (auto el : result1)
		cout << el << " ";
		
	cout << "\n___Task 3 Dejkstra___\n";
	vector<int>  result23 = Dikstra(matrix, 2);
	for (auto el : result23)
		cout << el << " ";
	
	cout << "\n___Task 4 Count Incidental Edges test___\n";
	vector<int> result2 = CountIncidentalEdges(matrix, 1);
	for (auto el : result2)
		cout << el << " ";

		

	char c; cin >> c;
	return 0;
}