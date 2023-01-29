
// floor[X_MAX][Y_MAX]
#include <iostream>
#include <vector>

#define KABE '*'

class Pos {
    public:
    int x; 
    int y;
};

class UnitMap {
    public:
    UnitMap() : v(-1), b_index(-1) {}

    int v;
    int b_index;
    int n_index;
};

const int kY = 30;
const int kX = 30;
UnitMap p_map[kY][kX];

const char floor[kY][kX+1] = {
    "******************************",
    "*111111   *                  *",
    "* 0*****  *                  *",
    "* ** *1*  *                  *",
    "* * **1*  *                  *",
    "* * *1 *  *                  *",
    "*11 **    *                  *",
    "****** ** *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      * *                  *",    
    "**      *                    *",    
    "******************************"   
};
void ClearPmap();
void PrintPmap();


//
// Get next_position
//
std::vector<Pos> NextPoints(const Pos& st) {
    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};

    std::vector<Pos> ans;

    for (int i = 0; i < 4; i++) {
        int nx = st.x + dx[i];
        int ny = st.y + dy[i];
        if (nx < 0 or kX <= nx) continue;
        if (ny < 0 or kY <= ny) continue;
        auto c = floor[nx][ny];        
        if (floor[nx][ny] == KABE) continue;
        
        if (p_map[nx][ny].v >= 0) continue;
        
        //p_map[nx][ny].b_index = (i + 2) % 4;
        p_map[nx][ny].b_index = i;
        
        p_map[nx][ny].v = p_map[st.x][st.y].v + 1;        
        
        ans.push_back({nx, ny});
        //printf("st (%02d, %02d) -> next(%02d, %02d) \n", st.x, st.y, nx, ny);
    }

    return ans;
}


void GetPointMap(const Pos& st)  {
    ClearPmap();
    p_map[st.x][st.y].v = 0;    
    //PrintPmap();    
    
    std::vector<Pos> n_points = NextPoints(st);    
    //PrintPmap();        
    //printf("first next points done\n") ;

    while (n_points.size()) {        
        std::vector<Pos> next_nps;
        for (const auto& p : n_points) {
            auto comp = NextPoints(p);
            next_nps.insert(next_nps.end(), comp.begin(), comp.end());
        }
        n_points = next_nps;

        //PrintPmap();        
    }

}

#include <algorithm>

std::vector<int> GetPath(const Pos& goal) {
    std::vector<int> path; 
    Pos trk = goal;    
    while (p_map[trk.x][trk.y].v >= 0) {
        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};

        int idx = p_map[trk.x][trk.y].b_index; 
        path.push_back(idx);

        printf("(%02d, %02d) v = %d, (%02d, %02d)\n", trk.x, trk.y, p_map[trk.x][trk.y].v, dx[idx], dy[idx]);

        trk.x -= dx[idx];
        trk.y -= dy[idx];
    }
    std::reverse(path.begin(), path.end());
    return path;
}



int main() {
    //PrintPmap();
    //printf("1st printpmap done\n") ;
    GetPointMap({2,2});
    printf("\n\nResult\n");
    PrintPmap();

    auto path = GetPath({1,8});
    
    printf("path \n");
    for (auto p : path) {
        printf("%d, ", p);
    }

    return 0;
}





void PrintPmap() {
    for (int i = 0; i < kY; i++) {
        for (int j = 0; j < kX; j++) {
            int p = p_map[i][j].v;
            printf("%02d ", p);
        }
        printf("\n");
    }
    return;
}

void ClearPmap() {
    for (int i = 0; i < kY; i++) {
        for (int j = 0; j < kX; j++) {
            p_map[i][j] = UnitMap();
        }
    }
    return;
}
