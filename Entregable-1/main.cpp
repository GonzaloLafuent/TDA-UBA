#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

//Para presentar el vector de forma correcta
void showVector(vector<string> v){
    cout<<"(";
        for (size_t i=0; i<v.size(); i++){
            if( i!= v.size()-1)  
                cout << v[i] << ", ";
            else cout<< v[i] << ")";  
        }   
    cout<< endl;
}

//Para dividr el vector entre defensores y delanteros
vector<string> sliceVector(size_t x,size_t j,vector<string> v){
    vector<string> r = {};
    for (size_t i = x; i< j; i++){
        r.push_back(v[i]);
    }
    sort(r.begin(),r.end());
    return r;
}

//Jugadores de mi caso de prueba tuple<nombre,ataque,defensa>
vector<tuple<string,int,int>> players = {};

//Mapeo los jugadores a una posicion de este array para saber cual seleccione
vector<int> map_players(10,0);

//jugadores que seleccione
vector<string> players_sel;

int sum_max_attackers = -1;
int sum_max_deffenders = -1; 

//Agrega los defensores a mi solucion parcial de acuerdo a los que todavia no seleccione
//y devuelve la suma de sus habilidades defensivas
int agregoDef(vector<string>& vector_players){
    int sum_deffenders = 0;
    for (size_t i = 0; i < map_players.size(); i++){
        if(map_players[i]==0){
            vector_players.push_back( get<0>(players[i]));
            sum_deffenders += get<2>(players[i]);
        }     
    }
    return sum_deffenders;
} 

void elegir_jugadores(int k,int j,int sum_parcial, vector<string>& player_sel_parcial){
    if(k == 5){
        if( sum_parcial > sum_max_attackers){
            //Caso: la suma de la habilidad de ataque de mi solucion parcial es mayor a la mejor que tenia
            sum_max_attackers = sum_parcial;
            players_sel = player_sel_parcial;

            sum_max_deffenders = agregoDef(players_sel);
        } else if (sum_parcial == sum_max_attackers){
            //Caso: la suma de la habilidad de ataque de mi solucion parcial es mayor a la mejor que tenia
            vector<string> player_comparar = player_sel_parcial;

            int sum_deffenders = agregoDef(player_comparar);

            if( sum_deffenders > sum_max_deffenders ) {
                //Si la suma de los defensores de mi solucion parcial es mayor la cambio por la mejor que tenia
                sum_max_deffenders = sum_deffenders;
                players_sel = player_comparar;
            } 
        }
    } else if(k < 5 && j < 10) {
        //Pruebo agregando el jugador de indice j
        player_sel_parcial.push_back(get<0>(players[j]));
        map_players[j] = 1;

        elegir_jugadores(k+1,j+1,sum_parcial + get<1>(players[j]), player_sel_parcial );
        
        //Pruebo no agregando el jugador de indice j 
        player_sel_parcial.pop_back();
        map_players[j] = 0;
        elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial);
    } 
}

int main(){
    int t = 0;
    cin>>t;
    vector<vector<tuple<string,int,int>>> cases = {};

    for (int i = 0; i < t; i++){ 
        players = {};

        for (size_t j = 0; j < 10; j++) {
            string name = "";
            int attack_ability = 0;
            int defense_ability = 0; 

            cin>>name>>attack_ability>>defense_ability;

            tuple<string,int,int> player = make_tuple(name,attack_ability,defense_ability);

            players.push_back(player);
        }

        cases.push_back(players);
    }

    for (size_t i = 0; i < cases.size(); i++){
        map_players = vector<int>(10,0);
        players_sel = {};

        sum_max_attackers = -1;
        sum_max_deffenders = -1;

        vector<string> sol_parcial = {};

        players = cases[i];

        //Al eneviar los jugadores ordenados por orden lexicografico
        //ascendete no tengoq ue realizar ninguna condicion para el desempate lexicografico
        sort(players.begin(),players.end());

        elegir_jugadores(0,0,0,sol_parcial);

        cout<<"Case "<<(i+1)<<":"<<endl;
        
        vector<string> attackers = sliceVector(0,5,players_sel);
        vector<string> deffenders = sliceVector(5,10,players_sel);

        showVector(attackers);    
        showVector(deffenders); 
    }
    
}
