/* programma poy elexei thn "apanthsh" toy xrhsth me thn swsth kai apodidei toys katallilous podous*/
#include <stdio.h>
#include <string.h>
#define SIZE 500
#define DIGITS "0123456789"
#define LETTERS "qwertyuiopasdfghjklzxcvbnm"
#define DIGITPOINTS 80  /* max points for correct digit tokens */
#define TEXTPOINTS (100-DIGITPOINTS) /* max points for correct letter tokens */

void point(char *table_ptr[500], char table_char[SIZE], char tokens[] ){
	int i=0;
	int j=0;
	
	/*elexo an ta tokens einai psifia h xarakthres*/
	if(strcmp("0123456789", tokens) == 0){
		/*kathe stoixeio toy pinaka pernei thn diefthinsi toy prwtoy stoixeioy toy pinaka table_char poy einai psifio*/
		do{
			table_ptr[j] = strpbrk(&table_char[i], tokens);
			j++;
			/*edw elengxw thn periptwsh poy ta dio prwta tokens apotelountai apo psifia*/
			if ( table_ptr[0] == table_ptr[1]){
				table_ptr[1] = NULL;
				j--;
			}
			i++;	/*auksanoyme to i wste o pinakas na synexisei sthn epomenh thesi*/
			/*phgainei sto shmeio toy pinaka table_char poy den einai "qwertyuiopasdfghjklzxcvbnm "*/
			while(strspn(&table_char[i], "qwertyuiopasdfghjklzxcvbnm ") == 0 &&  (i < strlen(table_char))){
				i++;
			}
			/*paravlepei ta ypoloipa psifia toy arithmou poy theloyme na deixnei o deikths*/
			while((strspn(&table_char[i], tokens) == 0 ) && (i < strlen(table_char))){
				i++;
			}
		}while(table_char[i] != '\0' && j<500);
	}
	if(strcmp("qwertyuiopasdfghjklzxcvbnm", tokens) == 0){
		/*kathe stoieio toy pinaka table_ptr pernei thn diefthinsi toy prwtoy stoixeioy tou pinaka table_char poy einai xarakthras*/
		do{
			table_ptr[j] = strpbrk(&table_char[i], tokens);
			j++;
			/*elexoume thn periptwsh poy ta dyo prwta tokens apoteloyntai apo xarakthres*/ 
			if ( table_ptr[0] == table_ptr[1]){
				table_ptr[1] = NULL;
				j--;
			}
			i++;	/*afksano to i wste na synexisei sthn epomenh thesi*/
			/*phgainei sto shmeio toy pinaka pou den einai "0123456789 "*/
			while(strspn(&table_char[i], "0123456789 ") == 0 &&  (i < strlen(table_char))){
				i++;
			}
			/*paravlepei tous ypoloipoys xarakthres ths leksis poy theloyme na deixnei o dikths*/
			while((strspn(&table_char[i], tokens) == 0 ) && (i < strlen(table_char))){
				i++;
			}
		}while(table_char[i] != '\0' && j<500);
	}
	/*sta stoixeia toy pinaka table_ptr poy den deixnoyn kapou, vazoume NULL*/
	for(i=j+1;i<500;i++){
		table_ptr[i] = NULL;
	}
}

double correction(char table_actual[SIZE], char table_expected[SIZE], char tokens[], int max_points){
	
	char *ptr_actual[500], *ptr_expected[500];
	int i,j=0,k=0,l=0,plithos_psifion=0,plithos_ison_psifion=0;
	double point_per_correct=0,points=0;
	char actual_str[500],expected_str[500];
	
	/*arxikopoio ton pinaka ws adeio*/
	for(i=0;i<500;i++){
		ptr_actual[i] = NULL;
		ptr_expected[i] = NULL;
	}
	
	point(ptr_actual, table_actual, tokens);
	point(ptr_expected, table_expected, tokens);
	
	/*vrisw posa kelia to pinaka den einai adia*/
	for(i=0;i<500;i++){
		if(ptr_actual[i] != NULL){
			l++;
		}
	}
	/*antigrafw ta strings pou deixnoyn kathe fora oi pinakes diktwn se alla strings*/
	for(i=0;i<l;i++){
		plithos_psifion=0;
		plithos_ison_psifion=0;
		if(ptr_actual[i] == NULL){
			break;
		}
		strcpy(actual_str,ptr_actual[i]);
		if(ptr_expected[i] == NULL){
			break;
		}
		strcpy(expected_str,ptr_expected[i]);
		
		k=0;
		do{
			plithos_psifion++;	/*metra ta psifia poy tha exei o arihmos h toys xarakthres poy tha exei h leksi mexri to keno*/
			if(actual_str[k] == expected_str[k]){
				plithos_ison_psifion++;	/*metra ta psifia poy einia isa h tous xaraktires poy einai idioi*/
			}
			k++;	/*afksano to k wste na proxorhsei sta epomena tvn strings*/
		}while(actual_str[k] != ' ' && expected_str[k] != ' ');
		if(plithos_psifion == plithos_ison_psifion){
			j++;	/*ayksanontas to j shmainei oti ena token einai swsto*/
		}
	}
	
	k=0;
	for(i=0;i<500;i++){ /*vriskw to synolo ton tokens poy periexei mia leksi*/
		if(ptr_expected[i] != NULL){
			k++;
		}
	}
	printf("\nCorrect tokens = %d out of %d\n", j,k);
	if(k==0){
		point_per_correct = 0;
	}
	else{
		point_per_correct = (max_points / (double)k);
	}
	if(j==0){
		if(strcmp("qwertyuiopasdfghjklzxcvbnm", tokens) == 0){
			points = 20;
		}
		else{
			points = 80;
		}
	}
	else {
		points =  (point_per_correct * (double)j);
	}
	return(points);
} 

int main(int argc, char *argv[]){
	
	char actual[SIZE], expected[SIZE], tokens_digits[] = "0123456789", tokens_LETTERS[] = "qwertyuiopasdfghjklzxcvbnm";
	int i;
	double points_from_digits=0,points_from_letters=0,points=0;
	
	printf("Actual: ");
	fgets(actual, SIZE, stdin);
	/*vriskw to \n kai to antikathistw me \0*/
	for(i=0;i<SIZE;i++){
		if(actual[i] == '\n'){
			actual[i] = '\0';
		}
		else{
			continue;
		}
	}
	
	printf("Expected: ");
	fgets(expected, SIZE, stdin);
	/*vriskw to \n kai to antikathistw me \0*/
	for(i=0;i<SIZE;i++){
		if(expected[i] == '\n'){
			expected[i] = '\0';
		}
		else{
			continue;
		}
	}
	
	points_from_digits = correction(actual, expected, tokens_digits, DIGITPOINTS);
	points_from_letters = correction(actual, expected, tokens_LETTERS, TEXTPOINTS);
	points = points_from_digits + points_from_letters;

	printf("\n%.2lf (%.2lf+%.2lf)\n", points, points_from_digits, points_from_letters);
	
	return 0;
}
