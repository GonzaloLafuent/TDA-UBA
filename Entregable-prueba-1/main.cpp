#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

vector<string> sliceVector(size_t x,size_t j,vector<string> v){
    vector<string> r = {};
    for (size_t i = x; i< j; i++){
        r.push_back(v[i]);
    }
    sort(r.begin(),r.end());
    return r;
}

void showPlayers(vector<string>& s){
    cout<<"(";
    for (size_t i=0; i<s.size(); i++){
        if( i!= s.size()-1)  
             cout << s[i] << ", ";
        else cout<< s[i] << ") ";  
    }   
    cout<< endl;
}

void showVector(vector<string>& s){
    for (size_t i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

vector<tuple<string,int,int>> players = {};

vector<int> map_players(10,0);
vector<string> players_sel;
vector<int> map_attackers_sel(10,0);

int sum_max_attackers = -1;
int sum_max_deffenders = -1; 

bool esta(string nombre,vector<string> vector_jugadores){
    bool esta = false;
    for (size_t i = 0; i < vector_jugadores.size() && !esta; i++){
        if( vector_jugadores[i] == nombre)
            esta = true;
    }
    return esta;
}

void orden_lexicografico(){
    vector<string> aux = {};
    for (size_t i = 0; i < 5; i++) {
        aux.push_back(players_sel[i]);
    }

    for (size_t i = 0; i < 5; i++){
        if(!esta(player_sel_parcial[i],players_sel))
            aux.push_back(player_sel_parcial[i]); 
    }

    sort(aux.begin(),aux.end());
    
    for (size_t i = 0; i < 5; i++){
        players_sel[i] = aux[i];
    }

}

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

            map_attackers_sel = map_players;

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

                map_attackers_sel = map_players;

                players_sel = player_comparar;
            } else if( sum_deffenders == sum_max_deffenders ){
                orden_lexicografico();
            }
        }
    } else if(k < 5 && j < 10) {
        player_sel_parcial.push_back(get<0>(players[j]));
        map_players[j] = 1;

        elegir_jugadores(k+1,j+1,sum_parcial + get<1>(players[j]), player_sel_parcial );
        
        player_sel_parcial.pop_back();
        map_players[j] = 0;
        elegir_jugadores(k,j+1,sum_parcial,player_sel_parcial);
    }
}


int main(){
    int t = 0;
    cin>>t;

    for (int i = 0; i < t; i++){
        map_players = vector<int>(10,0);
        players_sel = {};

        sum_max_attackers = -1;
        sum_max_deffenders = -1;

        vector<string> sol_parcial = {}; 
        players = {};

        for (size_t j = 0; j < 10; j++) {
            string name = "";
            int attack_ability = 0;
            int defense_ability = 0; 

            cin>>name>>attack_ability>>defense_ability;

            tuple<string,int,int> player = make_tuple(name,attack_ability,defense_ability);

            players.push_back(player);
        }
        
        elegir_jugadores(0,0,0,sol_parcial);

        cout<<"Case "<<(i+1)<<":"<<endl;
        
        vector<string> attackers = sliceVector(0,5,players_sel);
        vector<string> deffenders = sliceVector(5,10,players_sel);

        showPlayers(attackers);
        showPlayers(deffenders);
    }
        
    return 0; 
}
