




void FloydWarshall(int distancia[N][N]){


	int i, j, k;

	for (k=0; k<N; k++){
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){
				if (distancia[i][k] + distancia[k][j] < distancia[i][j]){
					distancia[i][j] = distancia[i][k] + distancia[k][j];
				}
			}
		}
	}
}
