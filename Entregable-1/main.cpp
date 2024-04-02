#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void orden_lexicografico(vector<string>& player_sel_parcial,vector<string>& attackers){
    vector<string> aux = {};
    //Agrego los nombres de los delanteros a ordenar
    for (size_t i = 0; i < 5; i++) {
        aux.push_back(attackers[i]);
        if( !count(attackers.begin(),attackers.end(),player_sel_parcial[i]) )
            aux.push_back(player_sel_parcial[i]);
    }

    //Los ordeno todo de forma lexicografica
    sort(aux.begin(),aux.end());
    
    //Agrego a la mejor solucion los delanteros de menor orden lexicografico
    for (size_t i = 0; i < 5; i++){
        attackers[i] = aux[i];
    }

} 

//k = llevo la cuenta de los elementos agregados
//j = posicion del jugador que veo si agrego o no
//sum_parcial = suma habilidad de defensores o atacantes
//player_sel_parcial = voy guardando la solucion
//players_sel[0] = attackers , players_sel[1] = deffenders
//max_sums[0] = sum_max_attackers, max_sums[1] = sum_max_deffenders
void elegir_jugadores(int k,int j,int sum_parcial, vector<string>& player_sel_parcial,
    vector<tuple<string,int,int>> players,vector<int>& max_sums,vector<int>& map_players,vector<vector<string>>& players_sel){
    if(k == 11){
        players_sel[1] = player_sel_parcial;
        max_sums[1] = sum_parcial;
    } else if(k == 5){
        if(max_sums[0] == -1){
            //1° caso: todavia no tuvimos ningun conjunto de delanteros
            max_sums[0] = sum_parcial;
            
            players_sel[0] = player_sel_parcial;

            vector<string> deffenders = {};
            elegir_jugadores(k+1,0,0,deffenders,players,max_sums,map_players,players_sel);
        } else if( sum_parcial > max_sums[0]){
            //2° caso: recibo un conjunto de delanteros cuya suma de habilidades es mayor a mi mejor solucion hasta ahora  
            max_sums[0] = sum_parcial;

            players_sel[0] = player_sel_parcial;

            vector<string> deffenders = {};
            elegir_jugadores(k+1,0,0,deffenders,players,max_sums,map_players,players_sel);
        } else if (sum_parcial == max_sums[0]){
            //3° caso: la suma de los delanteros es la misma a mi mejor solucion
            //Calculo las habilidades defensivas de la solucion parcial
            vector<string> deffenders = {};
            vector<int> sums(2,-1);
            elegir_jugadores(k+1,0,0,deffenders,players,sums,map_players,players_sel);

            //De ser mayor a la mejor solucion hasta ahora intercambiamos
            if( sums[1] > max_sums[1] ) {
                max_sums[1] = sums[1];
                players_sel[0] = player_sel_parcial;
                players_sel[1] = deffenders;
            } else if(sums[1] == max_sums[1] ){
                //Si estan empatados en defensa y en ataque paso al desempate lexicografico
                orden_lexicografico(player_sel_parcial,players_sel[0]);
            }
        }
    } else if(k < 5 && j<10) {
        //Cargo los delanteros
        player_sel_parcial.push_back(get<0>(players[j]));
        map_players[j] = 1;

        //Miro los subcojuntos de delanteos tomando al jugador j
        elegir_jugadores(k+1,j+1,sum_parcial + get<1>(players[j]), player_sel_parcial,players,max_sums,map_players,players_sel);

        player_sel_parcial.pop_back();
        map_players[j] = 0;

        //Miro los subconjuntos de delanteros no tomando al jugador j
        elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial,players,max_sums,map_players,players_sel);
    } else if(k > 5 && j < 10){
        //Cargo los defensores
        if( map_players[j] == 0){
            //Si el jugador no es delantero lo agrego como defensor
            player_sel_parcial.push_back(get<0>(players[j]));
            map_players[j] = 1;

            elegir_jugadores(k+1,j+1, sum_parcial + get<2>(players[j]),player_sel_parcial,players,max_sums,map_players,players_sel);
            map_players[j] = 0;
        } else elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial,players,max_sums,map_players,players_sel);
    } 
}


int main(){    
    int numb_cases = 0; 
    vector<vector<tuple<string,int,int>>> cases = {};
    
    cin>>numb_cases;

    for (int i = 0; i < numb_cases; i++){
        string name = "";
        int attack_ability = 0;
        int defense_ability = 0; 
        tuple<string,int,int> player;
        vector<tuple<string,int,int>> players = {};

        for (int j = 0; j < 10; j++){
            cin>>name>>attack_ability>>defense_ability;
            player = make_tuple(name,attack_ability,defense_ability);
            players.push_back(player);
        }

        cases.push_back(players);
    }
    

    for (size_t i = 0; i < cases.size(); i++) {
        vector<int> map_players = vector<int>(10,0);
        //players_sel[0] = attackers , players_sel[1] = deffenders
        vector<vector<string>>players_sel = {{},{}}; 

        //max_sums[0] = sum_max_attackers, max_sums[1] = sum_max_deffenders
        vector<int> max_sums(2,-1);

        //Solucion de delanteros parciales
        vector<string> sol_parcial = {}; 
        elegir_jugadores(0,0,0,sol_parcial,cases[i],max_sums,map_players,players_sel); 
    
        sort(players_sel[0].begin(),players_sel[0].end());
        sort(players_sel[1].begin(),players_sel[1].end());

        cout<<"Case "<<(i+1)<<":"<<endl;
        cout<<"(";
        for (size_t i=0; i<5; i++){
            if( i!= 4)  
                cout << players_sel[0][i] << ", ";
            else cout<< players_sel[0][i] << ") ";  
        }   
        cout<< endl;

        cout<<"(";
        for (size_t i=0; i<5; i++){
            if( i!= 4)  
                cout << players_sel[1][i] << ", ";
            else cout<< players_sel[1][i] << ") ";  
        }   
        cout<< endl;
    }

    return 0; 
}


