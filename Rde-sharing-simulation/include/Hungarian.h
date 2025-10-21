// Hungarian algorithm (a simple implementation for square cost matrices)
#pragma once
#include <vector>
#include <limits>

// Returns assignment as vector where result[i] = matched column for row i, or -1
std::vector<int> hungarian(const std::vector<std::vector<double>>& cost) {
    int n = (int)cost.size();
    if (n==0) return {};
    int m = (int)cost[0].size();
    int dim = std::max(n,m);
    std::vector<std::vector<double>> a(dim, std::vector<double>(dim, 0.0));
    const double INF = 1e12;
    for (int i=0;i<dim;i++){
        for (int j=0;j<dim;j++){
            if (i<n && j<m) a[i][j] = cost[i][j]; else a[i][j] = INF;
        }
    }

    std::vector<double> u(dim+1,0), v(dim+1,0);
    std::vector<int> p(dim+1,0), way(dim+1,0);
    for (int i=1;i<=dim;i++){
        p[0]=i;
        int j0=0;
        std::vector<double> minv(dim+1, INF);
        std::vector<char> used(dim+1,false);
        do{
            used[j0]=true;
            int i0=p[j0], j1=0;
            double delta=INF;
            for (int j=1;j<=dim;j++) if(!used[j]){
                double cur = a[i0-1][j-1]-u[i0]-v[j];
                if (cur<minv[j]){ minv[j]=cur; way[j]=j0; }
                if (minv[j]<delta){ delta=minv[j]; j1=j; }
            }
            for (int j=0;j<=dim;j++) if(used[j]){ u[p[j]]+=delta; v[j]-=delta; } else minv[j]-=delta;
            j0=j1;
        } while (p[j0]!=0);
        do{
            int j1=way[j0]; p[j0]=p[j1]; j0=j1;
        } while (j0);
    }
    std::vector<int> ans(n, -1);
    for (int j=1;j<=dim;j++){ if (p[j]<=n && j<=m) ans[p[j]-1]=j-1; }
    return ans;
}
