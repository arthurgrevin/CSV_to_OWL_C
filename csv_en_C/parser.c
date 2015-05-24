

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* concat (char* s1, char*s2){

	char* result;
    result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
	strcpy(result,s1);
	strcat(result,s2);
	return result;
}

int nb_ligne(FILE *f){
	int n=0,c;
	while((c=fgetc(f))!=EOF){
		if(c=='\n'){n++;}
	}
	printf("%d\n",n);
	return n;
}

int nb_colonne(char* str){
	int n=0;
	char* token;
	token=strtok(str,";");
	while(token!=NULL){
		n++;
		token=strtok(NULL,";");
	}
	printf("%d\n",n);
	return n;
}
int main(void){
	struct ligne{
		char* ligne[10];
	};
	struct ligne mat_out[8594];
	FILE* fichier;
	FILE* fichier_out;
	char str[1024];
	char* token;
	int ligne=0;
	int colonne=0;
	int i;
	fichier = fopen("paris.csv","r+");
	int n_l =nb_ligne(fichier)-1;
	fclose(fichier);
	fichier=fopen("paris.csv","r+");
	fgets(str,sizeof(char)*1024,fichier);
	int n_c = nb_colonne(str);

	
	char* tab_out [n_l][n_c];

	
	while(fgets(str,sizeof(char)*1024,fichier)!=NULL){
		//printf("%s\n",str);
		token=strtok(str,";"); 
		while(token!=NULL){
			//printf("test2\n");			
			//mat_out[ligne].ligne[colonne]=token;
			mat_out[ligne].ligne[colonne]=malloc(sizeof(char)*100);
			strcpy(mat_out[ligne].ligne[colonne],token);
			//printf("%s\n",mat_out[ligne].ligne[colonne]);
			colonne++;
			token = strtok(NULL,";");
		}
		colonne =0;
		printf("%s\n",mat_out[0].ligne[colonne]);		
		ligne++;
	}
	printf("%s\n",mat_out[0].ligne[0]);
	fclose(fichier);
	fichier=fopen("tp.owl","r+");
	fichier_out=fopen("result.owl","w+");
	while(fgets(str,sizeof(char)*1024,fichier)!=NULL){
		fprintf(fichier_out,"%s",str);
	}
	for(i=0;i<n_l;i++){
		fprintf(fichier_out,"<owl:NamedIndividual rdf:about=\"http://www.semanticweb.org/anthony/ontologies/2015/4/untitled-ontology-3#%d\">\n<rdf:type rdf:resource=\"http://www.semanticweb.org/anthony/ontologies/2015/4/untitled-ontology-3#Film\"/>\n<rdfs:label xml:\"fr\">%s</rdfs:label>\n</owl:NamedIndividual>\n\n",i,mat_out[i].ligne[0]);
	}
	fclose(fichier);
	fclose(fichier_out);
}
