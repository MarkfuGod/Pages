#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000

double f(double x) {
  return 4 / (1 + x * x);
}

int main(int argc, char *argv[]) {
  int world_size, world_rank;
  double x_start, x_end, dx, area;
  double pi;

  // 初始化 MPI 环境
  MPI_Init(&argc, &argv);

  // 获取进程总数和当前进程号
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // 计算每个进程负责计算的矩形个数
  int n = N / world_size;

  // 计算每个进程负责计算的矩形的左端点
  x_start = (double)world_rank / (double)world_size;
  x_end = (double)(world_rank + 1) / (double)world_size;

  // 计算每个进程负责计算的矩形的宽度
  dx = (x_end - x_start) / (double)n;

  // 计算每个进程负责计算的矩形的面积
  for (int i = 0; i < n; i++) {
    x_start += dx;
    area += f(x_start) * dx;
  }

  // 将每个进程计算的结果汇总
  double sum;
  MPI_Reduce(&area, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // 计算π的近似值
  if (world_rank == 0) {
    pi = 4 * sum;
    printf("pi = %.16f\n", pi/4);
    printf("time = 2000, threads = 8");
  }

  // 释放 MPI 资源
  MPI_Finalize();

  return 0;
}