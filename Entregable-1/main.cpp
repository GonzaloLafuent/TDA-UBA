#include <iostream>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

bool compareFunction (string x,string y) {return x < y;}

void showPlayers(vector<string>& s){
    cout<<"(";
    for (size_t i=0; i<s.size(); i++){
        if( i!= s.size()-1)  
             cout << s[i] << ", ";
        else cout<< s[i] << ") ";  
    }   
    cout<< endl;
}

vector<string> sliceVector(size_t x,size_t j,vector<string> v){
    vector<string> r = {};
    for (size_t i = x; i< j; i++){
        r.push_back(v[i]);
    }
    sort(r.begin(),r.end(),compareFunction);
    return r;
}

vector<int> map_players(10,0);
vector<string> players_sel;
vector<tuple<string,int,int>> players;

int sum_max_attackers = -1;
int sum_max_deffenders = -1; 

bool esta(string nombre,vector<string> vector_jugadores){
    //Esta funcion la uso para ver si el nombre de un jugador ya esta en un vector
    bool esta = false;
    for (size_t i = 0; i < vector_jugadores.size() && !esta; i++){
        if( vector_jugadores[i] == nombre)
            esta = true;
    }
    return esta;
}

void orden_lexicografico(vector<string>& player_sel_parcial){
    vector<string> aux = {};
    //En aux pongo todos los nombres de los delanteros de la solucion parcial
    for (size_t i = 0; i < 5; i++) {
        aux.push_back(player_sel_parcial[i]);
    }

    //Veo cuales se repiten en relacion a la mejor solucion que tengo hasta ahora
    for (size_t i = 0; i < 5; i++){
        if(!esta(players_sel[i],player_sel_parcial))
            aux.push_back(players_sel[i]); 
    }

    //Los ordeno todo de forma lexicografica
    sort(aux.begin(),aux.end(),compareFunction);
    
    //Dentro de mi mejor solucion no modifico los defensas
    //y agrego los delanteros de acuerdo a como se ordenaron lexicograficamente
    for (size_t i = 0; i < 5; i++){
        players_sel[i] = aux[i];
    }

} 

int elegir_jugadores(int k,int j,int sum_parcial, vector<string>& player_sel_parcial){
    if(k == 11){
        //Condicion para cuando complete el array con todos los jugadores
        //En este caso suma_parcial es igual a la suma de la habilidad de defensa de todos los defensas
        return sum_parcial;
    } else if(k == 5){
        if( sum_max_attackers == -1){
            //1° caso: todavia no tuvimos ningun conjunto de delanteros, por lo tanto
            //Esta se converte en la mejor solucion hasta ahora
            sum_max_attackers = sum_parcial;
            
            players_sel = player_sel_parcial;

            //Agrego los defensas y la suma total de sus habilidades defensivas
            sum_max_deffenders = elegir_jugadores(k+1,0,0,players_sel);
        } else if( sum_parcial > sum_max_attackers){
            //2° caso: recibo un conjunto de delanteros cuya suma de habilidades es mayor a mi mejo solucion  
            //Por lo tanto esta se transforma en la mejor  

            sum_max_attackers = sum_parcial;
            players_sel = player_sel_parcial;
            sum_max_deffenders = elegir_jugadores(k+1,0,0,players_sel);

        } else if (sum_parcial == sum_max_attackers){
            //3° caso: la suma de los delanteros es la misma, desempatan por habilidades defenivas
            vector<string> players_comparar = player_sel_parcial;

            //La suma de habilidades defensivas de la mejor solucion ya la tenemos calculada
            //Por lo tanto calculamos la de la solucion parcial con los defensas que quedan
            int sum_deffenders = elegir_jugadores(k+1,0,0,players_comparar);

            //De ser mayor a la mejor solucion hasta ahora intercambiamos
            if( sum_deffenders > sum_max_deffenders ) {
                sum_max_deffenders = sum_deffenders;
                players_sel = players_comparar;
            } else if(sum_deffenders == sum_max_deffenders ){
                //Si estan empatados en defensa y en ataque paso al desempate lexicografico
                orden_lexicografico(player_sel_parcial);
            }
        }
    } else if(k < 5 && j < 10) {
        //tomo al jugador y miro los posibles conjunto de delanteros con el
        //En este caso la suma parcial representa la suma de las habilidades de ataque
        player_sel_parcial.push_back(get<0>(players[j]));
        map_players[j] = 1;

        elegir_jugadores(k+1,j+1,sum_parcial + get<1>(players[j]), player_sel_parcial );

        //No tomo al jugador y miro los posibles conjuntos de delanteros sin el
        player_sel_parcial.pop_back();
        map_players[j] = 0;

        elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial);
    } else if(k > 5 && j < 10){
        //Esta caso los uso para ir agregando los defensores, en este caso la suma parcial
        //Se convierte en la suma de los valores de habilidades de los defensores
        if( map_players[j] == 0){
            //Si el elemento ya fue usado como delantero no lo ponemos
            player_sel_parcial.push_back(get<0>(players[j]));
            map_players[j] = 1;

            //Si se puede usar como defensa lo coloco en la solucion y sumo su habilida defensiva
            int suma_def = elegir_jugadores(k+1,j+1, sum_parcial + get<2>(players[j]),player_sel_parcial);
            map_players[j] = 0;

            return suma_def;
        } else return elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial);

    } 
    return 0;
}


int main(){
    string name = "";
    int attack_ability = 0;
    int defense_ability = 0; 
    int cases = 0; 

    tuple<string,int,int> player;

    for (int i = 0; i < 11; i++){
        if( i==0)
            cin>>cases;
        else{ 
            cin>>name>>attack_ability>>defense_ability;
            player = make_tuple(name,attack_ability,defense_ability);
            players.push_back(player);
        }
    }

    vector<string> sol_parcial = {}; 
    elegir_jugadores(0,0,0,sol_parcial);

    vector<string> attackers = sliceVector(0,5,players_sel);    
    vector<string> deffenders = sliceVector(5,10,players_sel);

    cout<<"Case 1"<<": "<<endl;
    showPlayers(attackers);
    showPlayers(deffenders);
    cout<<endl;

    return 0; 
}


