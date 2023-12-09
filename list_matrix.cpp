#include "list.h"

/***********  Matrix  **********/
string LC1275::tictactoe(vector<vector<int>>& moves) {
    /*井字遊戲給定一系列操作，求誰贏或平手*/
    // Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]] Output: "A"
    // Explanation: A wins, they always play first.
    // 关于井字棋游戏的，这个游戏简单容易上手，是课间十五分钟必备游戏之一，游戏规则很简单，一个人画叉，一个人画圆圈，只要有三个相连的位置，
    // 包括对角线就算赢。而这道题给了两个玩家的若干操作，让判断当前的棋盘状态，是哪一方赢了，还是没下完，或者是平局。判赢的条件就是找到任意行
    // 或列，或者对角线有三个相同的符号，若找不到有可能是平局或者没下完，只要判断总步数是否为9，就知道有没有下完了。由于给定的是两个玩家按顺
    // 序落子的位置，一个比较直接的方法就是分别还原出两个玩家在棋盘上的落子，分别还原出两个 3 by 3 的棋盘的好处是可以不用区分到底是叉还是圆
    // 圈，只要找三个连续的落子位置就行了，而且可以把查找逻辑放到一个子函数中进行复用。在子函数中，判断各行各列是否有连续三个落子，以及两条对
    // 角线，若有的话返回 true，否则 false。然后分别对还原出来的数组A和B调用子函数，若有返回的 true，则返回对应的A或B。否则就判断 moves
    // 数组的长度，若等于9，返回平局 Draw，反之为 Pending
    function<bool(vector<vector<bool>>)> win = [&](vector<vector<bool>> m) -> bool {
        for(int i=0; i<3; ++i) {
            if(m[i][0] && m[i][1] && m[i][2]) return true;
            if(m[0][i] && m[1][i] && m[2][i]) return true;
        }
        if(m[0][0] && m[1][1] && m[2][2]) return true;
        if(m[2][0] && m[1][1] && m[0][2]) return true;
        return false;
    };

    vector<vector<bool>> A(3, vector<bool>(3, false)), B=A;

    for(int i=0; i<moves.size(); ++i)
        if(i & 1) B[moves[i][0]][moves[i][1]] = true;
        else A[moves[i][0]][moves[i][1]] = true;
    if(win(A)) return "A";
    if(win(B)) return "B";
    return (moves.size() == 9) ? "Draw" : "Pending";
}

vector<vector<int>> LC1260::shiftGrid(vector<vector<int>>& grid, int k) {
    /*矩陣內元素向右移動k次*/
    // [1,2,3]    [9,1,2]
    // [4,5,6] -> [3,4,5]
    // [7,8,9]    [6,7,8]
    // Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
    // Output: [[9,1,2],[3,4,5],[6,7,8]]
    // 移动一个二维数组，移动方法是水平移动，即每个元素向右平移一位，行末尾的元素移动到下一行的开头，数组最后一个元素移动到开头的第一个元素，
    // 像这样移动k次，返回最终的数组。由于要移动k次，若每次都更新一遍数组的值，实在是不高效，最好直接能计算出最终状态的值，那么关注点就是计算
    // 一个元素水平移动k次的新位置。由于是二维数组，所以总是存在一个换行的问题，比较麻烦，一个很好的 trick 就是先将数组拉平，变成一维数组，
    // 这样移动k位就很方便，唯一需要注意是加k后可能超过一维数组的范围，需要当作循环数组来处理。明白了思路，代码就很好写了，新建一个和原数组同
    // 等大小的数组 res，然后遍历原数组，对于每个位置 (i, j)，计算其在拉平后的一维数组中的位置 i*n + j，然后再加上平移k，为了防止越界，最
    // 后再对 m*n 取余，得到了其在一维数组中的位置，将其转回二维数组的坐标，并更新结果 res 中的对应位置即可
    int m=grid.size(), n=grid[0].size(), len=m*n;
    if(!(k%len)) return grid; // k是len的倍數，等於沒有shift
    k %= len; // k簡化成len的餘數即可
    vector<vector<int>> res(m, vector<int>(n));

    for(int y=0; y<m; ++y)
        for(int x=0; x<n; ++x) {
            int idx = (y*n + x + k) % len;
            res[idx/n][idx%n] = grid[y][x];
        }
    return res;
}

int LC0892::surfaceArea(vector<vector<int>>& grid) {
    /*求一個三維積木堆的表面積*/
    // Input: grid =
    // [[1,2],
    //  [3,4]]
    // Output: 34
    // 给了我们一个二维数组 grid，其中 grid[i][j] 表示在位置 (i,j) 上累计的小正方体的个数，实际上就像搭积木一样，由这些小正方体来组成一个
    // 三维的物体，这里让我们求这个三维物体的表面积。我们知道每个小正方体的表面积是6，若在同一个位置累加两个，表面积就是10，三个累加到了一起
    // 就是14，其实是有规律的，n个小正方体累在一起，表面积是 4n+2。现在不仅仅是累加在一个小正方体上，而是在 nxn 的区间，累加出一个三维物体。
    // 由于之前做过那道三维物体投影的题 Projection Area of 3D Shapes，所以博主很思维定势的想到是不是也跟投影有关，然后又想当然的认为三维
    // 物体每一个面的面积就是该方向的投影，那么我们把三个方向的投影之和算出来，再乘以2不就是表面积了么？实际上这种方法是错误的，就拿题目中的例
    // 子4来说，当中间的小方块缺失了之后，实际上缺失的地方会产生出四个新的面，而这四个面是应该算在表面积里的，但是用投影的方法是没法算进去的。
    // 无奈只能另辟蹊径，实际上这道题正确的思路是一个位置一个位置的累加表面积，就类似微积分的感觉

    // 当n个小正方体累到一起的表面积是
    // 4n+1，而这个n就是每个位置的值 grid[i][j]，当你在旁边紧挨着再放一个累加的物体时，二者就会产生重叠，重叠的面数就是二者较矮的那堆正方体
    // 的个数再乘以2，明白了这一点，我们就可以从 (0,0) 位置开始累加，先根据 grid[0][0] 的值算出若仅有该位置的三维物体的表面积，然后向 (0,1)
    // 位置遍历，同样要先根据 grid[0][1] 的值算出若仅有该位置的三维物体的表面积，跟之前 grid[0][0] 的累加，然后再减去遮挡住的面积，通过
    // min(grid[0][0],grid[0][1])x2 来得到，这样每次可以计算出水平方向的遮挡面积，同时还需要减去竖直方向的遮挡面积
    // min(grid[i][j],grid[i-1][j])x2，这样才能算出正确的表面积
    int m=grid.size(), res=0;
    for(int y=0; y<m; y++)
        for(int x=0; x<m; x++) {
            int val = grid[y][x];
            if(val) res += 4*val + 2;
            if(y) res -= std::min(val, grid[y-1][x]) * 2;
            if(x) res -= std::min(val, grid[y][x-1]) * 2;
        }
    return res;
}

int LC0883::projectionArea(vector<vector<int>>& grid) {
    /*求一三維物體在三個方向投影面積之和*/
    // Input: grid =
    // [[1,2],
    //  [3,4]]
    // Output: 17
    // Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
    // 给了我们一个二维数组 grid，用来表示一个 3D 物体形状，表示方法是 grid[i][j] 表示在 (i, j) 位置上的高度，就像垒积木一样，累出了一个
    // 三维物体。然后让我们计算三个方向的投影面积之和，所谓的三个方向分别是上方 Top，前方 Front，和侧方 Side。用过一些三维建模软件（例如
    // Maya， 3DMax）的同学，对这个应该不陌生。我们先来考虑正上方投影面积如何计算，由于题目中说了 grid 数组的宽和高相等，那么上方投影就是一
    // 个正方形，前提是每个 grid[i][j] 的值都大于0的话。因为若 grid 数组中有0存在，则表示正方形投影会缺少了一块。由于这个大的正方形投影是
    // 由 nxn 个小的正方形组成，那么实际上我们只要统计出小正方形的个数，那么大正方形投影的面积也就知道了（是不有点微积分的感觉）。所以我们在
    // 遍历的过程中，只要判断若 grid[i][j] 大于0，则结果 res 自增1即可。下面再来考虑另外两个方向的投影怎么计算，另两个方向的投影的可能是
    // 不规则图形，参见题目中给的那个图，如果仔细观察的话，其投影图像的每个阶段的高其实就是各行或各列中的最大值，这也不难理解，就像城市中耸立
    // 的高度不同的大楼，若要描出城市的轮廓，那么描出来的肯定都是每个位置上最高建筑物的轮廓。那么问题就变成了累加各行各列的最大值。我们实际上
    // 在一次遍历中就能完成，使用了一个小 trick，那就是在第二层 for 循环中，行最大值 rowMax 就是不断用 grid[i][j] 来更新，而列最大值
    // colMax 就是不断用 grid[j][i] 来更新，巧妙的交换i和j，实现了目标。然后分别把更新出来的行列最大值加到结果 res 中即可
    int m=grid.size();
    int res=0;
    for(int y=0; y<m; y++) {
        int rowMax=0, colMax=0;
        for (int x = 0; x < m; x++) {
            if(grid[y][x]) res++;
            rowMax = std::max(rowMax, grid[y][x]);
            colMax = std::max(colMax, grid[x][y]);
        }
        res += rowMax + colMax;
    }
    return res;
}

vector<vector<int>> LC0867::transpose(vector<vector<int>>& matrix) {
    /*求轉置後的矩陣*/
    // [[1,2,3],   [[1,4,7],
    //  [4,5,6], -> [2,5,8],
    //  [7,8,9]]    [3,6,9]]
    // 转置一个矩阵，在大学的线性代数中，转置操作应该说是非常的常见。所谓矩阵的转置，就是把 mxn 的矩阵变为 nxm 的，并且原本在 A[i][j] 位置
    // 的数字变到 A[j][i] 上即可，非常的简单直接。而且由于此题又限定了矩阵的大小范围为 [1, 1000]，所以不存在空矩阵的情况，因而不用开始时对
    // 矩阵进行判空处理，直接去获取矩阵的宽和高即可。又因为之前说了转置会翻转原矩阵的宽和高，所以我们新建一个 nxm 的矩阵，然后遍历原矩阵中的每
    // 个数，将他们赋值到新矩阵中对应的位置上即可
    int m=matrix.size(), n=matrix[0].size();
    vector<vector<int>> res(n, vector<int>(m));
    for(int y=0; y<m; y++)
        for(int x=0; x<n; x++)
            res[x][y] = matrix[y][x];
    return res;
}

vector<vector<int>> LC0832::flipAndInvertImage(vector<vector<int>>& image) {
    /*求矩陣水平方向翻轉後每個元素取反數*/
    // [[1,1,0],   [[1,0,0],
    //  [1,0,1], -> [0,1,0],
    //  [0,0,0]]    [1,1,1]]
    // Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
    // Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
    // 这道题让我们翻转图像，翻转的方法是对于二维数组的每一行，先将所有元素位置翻转一下，然后再按顺序将每个像素值取个反。既然要求这么直接明了，
    // 那么就按照其说的一步一步来呗，首先翻转每一行，记得一定要加 ‘&’ 号，不然原数组不会被修改。然后在遍历每个数字，让其或上1，达到取反的目的，
    // 当然还是必须要加 ‘&’ 号，最后返回修改后的A数组即可
//    for(auto &row:image)
//        std::reverse(row.begin(), row.end());
//    for(auto &row:image)
//        for(auto &e:row)
//            e ^= 1;
//    return image;

    // 上面的方法虽然直接了当，但是毕竟修改了原数组A，再来看一种不修改的方法，这里我们新建一个跟A一样长的二维数组，只不过里面的各行还是空的。
    // 然后我们遍历A数组的各行，但在遍历各行上的数字时，我们采用从后往前的遍历顺序，然后对于每个数字取反在加入结果res中，这样直接将翻转和取
    // 反同时完成了
    int n=image.size();
    vector<vector<int>> res(n);
    for(int y=0; y<n; y++)
        for(int x=n-1; x>=0; x--)
            res[y].push_back(!image[y][x]); // push_back到第y row
    return res;
}

bool LC0766::isToeplitzMatrix(vector<vector<int>>& matrix) {
    /*問一矩陣每條從左上到右下對角線的值是否都相等*/
    // Input: matrix =
    // [[1,2,3,4],
    //  [5,1,2,3],
    //  [9,5,1,2]]
    // Output: true
    // 这道题让我们验证一个矩阵是否是托普利兹矩阵Toeplitz Matrix，所谓的这个托普利兹矩阵，就是看每条从左上到右下的对角线是否是值都相等。
    // 注意矩阵的行数列数不一定相等，要验证所有的对角线。那么其实这道题的本质是让我们斜向遍历矩阵，就是按对角线来。按正常顺序来遍历数组，
    // 对于每个遍历到的数字，都跟其右下方的数字对比，如果不相同，直接返回false即可。为了防止越界，我们不遍历最后一行和最后一列，遍历完成后，
    // 返回true
    for(int y=0; y<matrix.size()-1; y++)
        for(int x=0; x<matrix[0].size()-1; x++)
            if(matrix[y][x] != matrix[y+1][x+1]) return false;
    return true;
}

vector<vector<int>> LC0661::imageSmoother(vector<vector<int>>& img) {
    /*求矩陣每一元素跟相鄰元素算平均*/
    // [[100,200,100],   [[137,141,137],
    //  [200,50,200], ->  [141,138,141],
    //  [100,200,100]]    [137,141,137]]
    // Explanation:
    // For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) = floor(137.5) = 137
    // For the points (0,1), (1,0), (1,2), (2,1): floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141
    // For the point (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) = 138
    // 给一个图片进行平滑处理，一般来说都是用算子来跟图片进行卷积，但是由于这道题只是个Easy的题目，我们直接用土办法就能解了，就直接对于每一个
    // 点统计其周围点的个数，然后累加像素值，做个除法就行了，注意边界情况的处理
    if(img.empty() || img[0].empty()) return {};
    const int m=img.size(), n=img[0].size();
    vector<vector<int>> res=img, dirs{ {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1} }; // {x, y}
    for(int y=0; y<m; y++)
        for(int x=0; x<n; x++) {
            int val = img[y][x], cnt = 1;
            for(auto dir:dirs) {
                int col=x+dir[0], raw=y+dir[1];
                if(col<0 || col>=n || raw<0 || raw>=m) continue;
                val+=img[raw][col];
                cnt++;
            }
            res[y][x] = val/cnt;
        }
    return res;
}

vector<vector<int>> LC0566::matrixReshape(vector<vector<int>>& mat, int r, int c) {
    // 遍历拉直后的一维数组的坐标，然后分别转换为两个二维数组的坐标进行赋值
    int m=mat.size(), n=mat[0].size();
    if(m*n != r*c) return mat;
    vector<vector<int>> res(r, vector<int>(c));
    for(int i=0; i<r*c; i++)
        res[i/c][i%c]=mat[i/n][i%n];
    return res;
}

int LC0463::islandPerimeter(vector<vector<int>>& grid) {
    // 这道题给了我们一个格子图，若干连在一起的格子形成了一个小岛，规定了图中只有一个相连的岛，且岛中没有湖，让我们求岛的周长。我们知道一个格
    // 子有四条边，但是当两个格子相邻，周围为6，若某个格子四周都有格子，那么这个格子一条边都不算在周长里。那么我们怎么统计出岛的周长呢？
    // 对于每个岛屿格子先默认加上四条边，然后检查其左面和上面是否有岛屿格子，有的话分别减去两条边，这样也能得到正确的结果
    if(grid.empty() || grid[0].empty()) return 0;
    int res=0, m=grid.size(), n=grid[0].size();
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            if(!grid[i][j]) continue;
            res+=4;
            if(i && grid[i-1][j]) res-=2;
            if(j && grid[i][j-1]) res-=2;
        }
    return res;
}