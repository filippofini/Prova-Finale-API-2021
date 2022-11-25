#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void max_heapify(unsigned long int*, unsigned long int*, unsigned long int, unsigned long int) ;
void cancella_max(unsigned long int*, unsigned long int*, unsigned long int) ;
void inserisci(unsigned long int*, unsigned long int*, unsigned long int, unsigned long int, unsigned long int) ;
void swap(unsigned long int*, unsigned long int*) ;


int main(){

	int check, i ;
	unsigned long  n_nodi, l_classifica, input ;
	unsigned long int somma_array_nodi, count_grafi, end_input, count, index ;
	unsigned long int j, max, min, pos_min, curr_min, pos_prec, add_vuoto ;
	unsigned long long int percorso_corrente, percorso_futuro, percorso_totale ;
	unsigned long int *array_grafo, *array_nodi, *array_best_grafi, *pos_best_grafi ;
	double *array_distanze ;
	char add_grafo[14], *input_valori, *end, *controllo_valori, *new_pos_best_grafi  ;


	check = scanf("%lu", &n_nodi) ;
	check = scanf("%lu", &l_classifica) ;

	array_best_grafi = (unsigned long int*)malloc(l_classifica*sizeof(unsigned long int)) ;
	pos_best_grafi = (unsigned long int*)malloc(l_classifica*sizeof(unsigned long int)) ;

	

	if(check==1){
		end_input = 0 ;
	}

	count_grafi = 0 ;
	add_vuoto = 0 ;

	array_grafo = (unsigned long int*)malloc(n_nodi*n_nodi*sizeof(unsigned long int)) ;
	input_valori = (char*)malloc((n_nodi+n_nodi*10)*sizeof(char)) ;
	array_nodi = (unsigned long int*)malloc(n_nodi*sizeof(unsigned long int)) ;
	array_distanze = (double*)malloc(n_nodi*sizeof(double)) ;



	while(end_input==0){

		check = scanf("%s", add_grafo) ;


		if(check==1 && strcmp(add_grafo, "AggiungiGrafo")==0){
			
			input_valori = fgets(input_valori,n_nodi+n_nodi*10, stdin) ;
			for(i=0;i<n_nodi;i++){
				input_valori = fgets(input_valori,n_nodi+n_nodi*10, stdin) ;
				controllo_valori = input_valori ;
				
				for(j=0;j<n_nodi;j++){
					input = strtoul(controllo_valori, &end, 10) ;
					controllo_valori = end + 1 ;
					array_grafo[j+n_nodi*i] = input ;
				}
			}

			count_grafi++ ;


			//INIZIO IMPLEMENTAZIONE DIJKSTRA



			//creo array contenente tutti i nodi
				for(i=0;i<n_nodi;i++){
				array_nodi[i] = i ;
			}
			//pongo le distanze dal primo nodo di ogni nodo a infinito
			for(i=0;i<n_nodi;i++){
				array_distanze[i] = INFINITY ;
			}
			array_distanze[0] = 0 ;

			somma_array_nodi = 0 ;
			for(i=0;i<n_nodi;i++){
				somma_array_nodi = array_nodi[i]+somma_array_nodi ;
			}

			pos_min = 0 ;
			curr_min = 0 ;
			pos_prec = 0 ;

			percorso_futuro = 0 ;
			percorso_corrente = 0 ;

				
			for(i=0,count=0;i<n_nodi;i++){
				if(array_grafo[i]!=0){
					percorso_futuro = percorso_corrente + array_grafo[i] ;
					count++ ;
					if(percorso_futuro<array_distanze[i]){
						array_distanze[i] = percorso_futuro ;
					}
				}
			}
				
			if(count==0){
				for(i=0;i<n_nodi;i++){
					array_distanze[i] = 0 ;
				}
				somma_array_nodi = 0 ;
			}

			percorso_corrente = array_distanze[pos_min] ;


			count = 0 ;
			while(somma_array_nodi!=0){

				min = 0 ;
				for(i=0;i<n_nodi;i++){
					if(min==0 && array_distanze[i]!=0 && array_nodi[i]!=0){
						min = array_distanze[i] ;
					}
					if(array_distanze[i]!=0 && array_distanze[i]<=min && array_nodi[i]!=0){
						min = array_distanze[i] ;
						curr_min = i ;
					}
				}


				array_nodi[curr_min] = 0 ; //rimuovo il nodo più vicino dall'array dei nodi

				percorso_corrente = array_distanze[curr_min] ;

				pos_prec = pos_min ;
				pos_min = curr_min ;

				
				for(i=0;i<n_nodi;i++){
					if(array_grafo[pos_min*n_nodi+i]!=0 && pos_min*n_nodi+pos_min!=pos_min*n_nodi+i && pos_min*n_nodi+pos_prec!=pos_min*n_nodi+i){
						percorso_futuro = percorso_corrente + array_grafo[pos_min*n_nodi+i] ;
					

						if(percorso_futuro<array_distanze[i]){
							array_distanze[i] = percorso_futuro ;
						}
					}
				}

				count++ ;
				if(count>n_nodi){
					for(i=0;i<n_nodi;i++){
						array_nodi[i] = 0 ;
						if(array_distanze[i]==INFINITY)
							array_distanze[i] = 0 ;
					}
				}
				
				
				for(i=0,somma_array_nodi=0;i<n_nodi;i++){
					somma_array_nodi = array_nodi[i] + somma_array_nodi ;
				}

			}


			percorso_totale = 0 ;
			for(i=1;i<n_nodi;i++){
				percorso_totale = (unsigned long int)array_distanze[i] + percorso_totale ;
			}
			
			
			//aggiungo i primi grafi
			if(l_classifica>=count_grafi){
				array_best_grafi[add_vuoto] = percorso_totale ;
				pos_best_grafi[add_vuoto] = count_grafi-1 ;
				add_vuoto++ ;
			}

			if(l_classifica==count_grafi-1){
				for(i=l_classifica/2;i>=0;i--){
					max_heapify(array_best_grafi, pos_best_grafi, i, l_classifica) ;
				}
			}

			//controllo se il percorso del grafo attuale è minore, se sì rimuovo il maggiore
			if(l_classifica<count_grafi){
				max = array_best_grafi[0] ;
				if(max>percorso_totale){
					cancella_max(array_best_grafi, pos_best_grafi, l_classifica) ;
					inserisci(array_best_grafi, pos_best_grafi, percorso_totale, count_grafi-1, l_classifica) ;
				}
			
			}
		}


		if(check==1 && strcmp(add_grafo, "TopK")==0){

			if(count_grafi<l_classifica){
				new_pos_best_grafi = (char*)malloc((count_grafi*10+count_grafi)*sizeof(char)) ;
				for(i=0,index=0;i<count_grafi;i++){
					if(pos_best_grafi[i]==0 && i==0){
						index+=sprintf(&new_pos_best_grafi[index],"%lu",pos_best_grafi[i]) ;
						index+=sprintf(&new_pos_best_grafi[index],"%s"," ") ;
					}
					if(pos_best_grafi[i]!=0){
						index +=sprintf(&new_pos_best_grafi[index],"%lu",pos_best_grafi[i]) ;
						if(i!=count_grafi-1){
							index +=sprintf(&new_pos_best_grafi[index],"%s"," ") ;
						}
					}
				}

				fputs(new_pos_best_grafi, stdout) ;
				printf("\n") ;

				free(new_pos_best_grafi) ;

			}
			else{
				new_pos_best_grafi = (char*)malloc((l_classifica*10+l_classifica)*sizeof(char)) ;
				for(i=0,index=0;i<l_classifica;i++){
					index +=sprintf(&new_pos_best_grafi[index],"%lu",pos_best_grafi[i]) ;
					if(i!=l_classifica-1){
						index +=sprintf(&new_pos_best_grafi[index],"%s"," ") ;
					}
				}

				fputs(new_pos_best_grafi, stdout) ;
				printf("\n") ;

				free(new_pos_best_grafi) ;
			}
		}
		if(check==EOF){
			end_input = 1 ;
		}
	}

	free(array_distanze) ;
	free(array_nodi) ;
	free(input_valori) ;
	free(array_grafo) ;
	free(array_best_grafi) ;
	free(pos_best_grafi) ;

	return 0 ;
}






void max_heapify(unsigned long int* array_best_grafi ,unsigned long int* pos_best_grafi, unsigned long int n, unsigned long int l_classifica){
	unsigned long int l, r, pos_max ;

	l = 2*n+1 ;
	r = 2*n+2 ;

	if(l<=l_classifica && array_best_grafi[l]>array_best_grafi[n]){
		pos_max = l ;
	}else{
		pos_max = n ;
	}

	if(r<=l_classifica && array_best_grafi[r]>array_best_grafi[pos_max]){
		pos_max = r ;
	}

	if(pos_max!=n){
		swap(&pos_best_grafi[n], &pos_best_grafi[pos_max]) ;
		swap(&array_best_grafi[n], &array_best_grafi[pos_max]) ;
		max_heapify(array_best_grafi, pos_best_grafi, pos_max, l_classifica) ;
	}
}



void cancella_max(unsigned long int *array_best_grafi, unsigned long int *pos_best_grafi, unsigned long int l_classifica){

	if (l_classifica<0){
		return ;
	}

	array_best_grafi[0] = array_best_grafi[l_classifica-1] ;
	pos_best_grafi[0] = pos_best_grafi[l_classifica-1] ;

	l_classifica = l_classifica - 1 ;

	max_heapify(array_best_grafi, pos_best_grafi, 0, l_classifica) ;
}


void inserisci(unsigned long int *array_best_grafi, unsigned long int *pos_best_grafi, unsigned long int percorso_totale, unsigned long int count_grafi, unsigned long int l_classifica){
	long int i ;

	array_best_grafi[l_classifica-1] = percorso_totale ;
	pos_best_grafi[l_classifica-1] = count_grafi ;

	i = l_classifica ;
	while(i>0 && array_best_grafi[(i-1)/2]<array_best_grafi[i]){
		swap(&pos_best_grafi[(i-1)/2], &pos_best_grafi[i]) ;
		swap(&array_best_grafi[(i-1)/2], &array_best_grafi[i]) ;
		i = (i-1)/2 ;
	}
}





void swap(unsigned long int *a, unsigned long int *b){
	unsigned long int tmp ;

	tmp = *a ;
	*a = *b ;
	*b = tmp ;
}
