#include <cell_world.h>
#include <params_cpp.h>
#include <iostream>



using namespace params_cpp;
using namespace cell_world;
using namespace std;
using namespace json_cpp;


int main (int argc, char **argv){
    string new_world = "22_01";    // input new world naem here or as program argument

    Parser p(argc,argv);
    auto occlusions = p.get(Key("-o","--occlusions"), new_world);
    World world = World::get_from_parameters_name("hexagonal","canonical", occlusions);
    Graph graph = world.create_graph();
    Cell_group cells = world.create_cell_group().free_cells();
    Cell_group pd;
    for (const Cell &cell:cells) {
        if (graph.is_connected(cell,world.cells[0])){
            pd.add(cell);
        }
    }


    pd.save("../../cellworld_data/cell_group/hexagonal."+ occlusions +".predator_destinations");  // MAKE SURE WORLD ARE IS NAMED PROPERLY
    cout << "done....." << endl;
    cout << " New predator destinations created for: " << occlusions  << endl;
    cout << pd << endl;
}