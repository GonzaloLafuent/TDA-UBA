#include <iostream>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

void showVector(vector<string>& s){
    for (size_t i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

// tuple( nombre del jugador , habilidad de ataque , habilidad de defensa )
vector<tuple<string,int,int>> players = {
    make_tuple("sameezahur",20,21),
    make_tuple("sohelh",18,9),
    make_tuple("jaan",17,86),
    make_tuple("sidky",16,36),
    make_tuple("shamim",16,18),
    make_tuple("shadowcoder",12,9),
    make_tuple("muntasir",13,4),
    make_tuple("brokenarrow",16,16),
    make_tuple("emotionalblind",16,12),
    make_tuple("tanaeem",20,97)
};

vector<int> map_players(10,0);
vector<string> players_sel;
vector<int> map_attackers_sel = {};

int sum_max_attackers = -1;
int sum_max_deffenders = -1;

bool compareFunction (string x,string y) {return x<y;} 

bool esta(string nombre,vector<string> vector_jugadores){
    bool esta = false;
    for (size_t i = 0; i < vector_jugadores.size() && !esta; i++){
        if( vector_jugadores[i] == nombre)
            esta = true;
    }
    return esta;
}

void orden_lexicografico(vector<string>& player_sel_parcial){
    vector<string> aux = {};
    for (size_t i = 0; i < 5; i++) {
        aux.push_back(player_sel_parcial[i]);
    }

    for (size_t i = 0; i < 5; i++){
        if(!esta(players_sel[i],player_sel_parcial))
            aux.push_back(players_sel[i]); 
    }

    sort(aux.begin(),aux.end(),compareFunction);
    
    for (size_t i = 0; i < 5; i++){
        players_sel[i] = aux[i];
    }

}

//Agrego los que quedan libres como defensensores, para el caso que 
//No hay que comparar la defensa
int agregoDef(vector<string>& players_sel){
    int sum_deffenders = 0;
    for (size_t i = 0; i < map_players.size(); i++){
        if(map_players[i]==0){
            players_sel.push_back( get<0>(players[i]));
            sum_deffenders += get<2>(players[i]);
        }     
    }
    return sum_deffenders;
} 

void elegir_jugadores(int k,int j,int sum_parcial, vector<string>& player_sel_parcial){
    if(k == 5){
        if( sum_max_attackers == -1){
            sum_max_attackers = sum_parcial;
            players_sel = player_sel_parcial;
            sum_max_deffenders = agregoDef(players_sel);
        } else if( sum_parcial > sum_max_attackers){
            sum_max_attackers = sum_parcial;
            players_sel = player_sel_parcial;
            map_attackers_sel = map_players;
            sum_max_deffenders = agregoDef(players_sel);
        } else if (sum_parcial == sum_max_attackers){
            vector<string> player_comparar = player_sel_parcial;
            int sum_deffenders = agregoDef(player_comparar);
            if( sum_deffenders > sum_max_deffenders ) {
                sum_max_deffenders = sum_deffenders;
                players_sel = player_comparar;
            } else if( sum_deffenders == sum_max_deffenders ){
                orden_lexicografico(player_sel_parcial);
            }
        }
    } else if(k < 5 && j < 10) {
        player_sel_parcial.push_back(get<0>(players[j]));
        map_players[j] = 1;
        elegir_jugadores(k+1,j+1,sum_parcial + get<1>(players[j]), player_sel_parcial );
        player_sel_parcial.pop_back();
        map_players[j] = 0;
        elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial);
        /*
        for (size_t i = 0; i < map_players.size(); i++){
            if(map_players[i] == 0){
                map_players[i] = 1;
                player_sel_parcial.push_back( get<0>(players[i]));

                elegir_jugadores(k+1,sum_parcial + get<1>(players[i]),player_sel_parcial);

                map_players[i] = 0;
                player_sel_parcial.pop_back();
            }    
        }
        */
    }
}


int main(){
    /*
    string name = "";
    int attack_ability = 0;
    int defense_ability = 0; 
    vector<tuple<string,int,int>> players = {};

    tuple<string,int,int> player;

    Ingreso de datos por consola
    for (size_t i = 0; i < 10; i++){
        cin>>name;
        cin>>attack_ability;
        cin>>defense_ability;

        player = make_tuple(name,attack_ability,defense_ability);
        players.push_back(player);
    }
    */
    vector<string> sol_parcial = {}; 
    elegir_jugadores(0,0,0,sol_parcial);

    cout<<players_sel.size()<<endl;

    showVector(players_sel);
    return 0; 
}


