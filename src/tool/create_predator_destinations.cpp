#include <cell_world.h>
#include <params_cpp.h>
#include <iostream>



using namespace params_cpp;
using namespace cell_world;
using namespace std;
using namespace json_cpp;


int main (int argc, char **argv){
    string new_world = "21_05";    // input new world name here or as program argument

    Parser p(argc,argv);
    auto occlusions = p.get(Key("-o","--occlusions"),new_world);
    World world = World::get_from_parameters_name("hexagonal","canonical", occlusions);
    Graph graph = world.create_graph();
    Cell_group cells = world.create_cell_group().free_cells();
    Graph g = world.create_graph();
    Cell_group pd;
    for (const Cell &cell:cells) {
        if (graph.is_connected(cell,world.cells[0]) && g[cell].size() == world.connection_pattern.size()){  // if the cell is connected to the entrance and surrounded by free cells add it to destination list
            pd.add(cell);
        }
    }


    pd.save("./hexagonal."+ occlusions +".predator_destinations");  // MAKE SURE WORLD ARE IS NAMED PROPERLY
    cout << "done....." << endl;
    cout << " New predator destinations created for: " << occlusions  << endl;
    cout << pd << endl;
}
