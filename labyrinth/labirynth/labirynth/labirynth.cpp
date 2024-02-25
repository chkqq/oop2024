#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <string>

using namespace std;

const char WALL = '#';
const char START = 'A';
const char END = 'B';
const char PATH = '.';

// Structure to represent a point in the labyrinth
struct Point {
    int x, y;
};

// Function to check if a point is valid in the labyrinth
bool isValid(int x, int y, int rows, int cols, vector<vector<char>>& labyrinth) {
    return (x >= 0 && x < rows&& y >= 0 && y < cols&& labyrinth[x][y] != WALL);
}

// Function to perform BFS to find the shortest path
vector<Point> findShortestPath(vector<vector<char>>& labyrinth, Point start, Point end) {
    int rows = labyrinth.size();
    int cols = labyrinth[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, { -1, -1 }));
    queue<Point> q;

    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == end.x && curr.y == end.y) {
            // Reconstruct path
            vector<Point> path;
            while (!(curr.x == start.x && curr.y == start.y)) {
                path.push_back(curr);
                curr = parent[curr.x][curr.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        int dx[] = { -1, 0, 1, 0 };
        int dy[] = { 0, 1, 0, -1 };
        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            if (isValid(newX, newY, rows, cols, labyrinth) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                parent[newX][newY] = curr;
                q.push({ newX, newY });
            }
        }
    }

    // If no path found, return an empty path
    return vector<Point>();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cout << "Error: Unable to open input file.\n";
        return 1;
    }

    // Read the labyrinth from the input file
    vector<vector<char>> labyrinth;
    string line;
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        labyrinth.push_back(row);
    }
    inputFile.close();

    // Find start and end points
    Point start, end;
    bool foundStart = false, foundEnd = false;
    for (int i = 0; i < labyrinth.size(); ++i) {
        for (int j = 0; j < labyrinth[i].size(); ++j) {
            if (labyrinth[i][j] == START) {
                start = { i, j };
                foundStart = true;
            }
            else if (labyrinth[i][j] == END) {
                end = { i, j };
                foundEnd = true;
            }
            if (foundStart && foundEnd) break;
        }
        if (foundStart && foundEnd) break;
    }

    if (!foundStart || !foundEnd) {
        cout << "Error: Start or end point not found.\n";
        return 1;
    }

    // Find the shortest path
    vector<Point> shortestPath = findShortestPath(labyrinth, start, end);

    // Mark the path in the labyrinth
    for (const auto& point : shortestPath) {
        labyrinth[point.x][point.y] = PATH;
    }

    // Write the labyrinth with the marked path to the output file
    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cout << "Error: Unable to open output file.\n";
        return 1;
    }
    for (const auto& row : labyrinth) {
        for (char cell : row) {
            outputFile << cell;
        }
        outputFile << '\n';
    }
    outputFile.close();

    cout << "Shortest path found and written to output file.\n";

    return 0;
}
