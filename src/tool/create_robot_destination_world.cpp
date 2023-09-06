#include <cell_world/paths.h>
#include <cell_world/map.h>
#include <cell_world.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace cell_world;





int main(){
    string new_world = "oasis_14_02";    // input new world name here or as program argument


    auto occlusions = new_world;
    World world = World::get_from_parameters_name("hexagonal","canonical", occlusions);
    Graph graph = world.create_graph();
    Cell_group cg = world.create_cell_group();
    Cell_group free_cells = cg.free_cells();
    Graph g = world.create_graph();
    Map map (world.create_cell_group());
    for (const Cell &cell:free_cells) {
        if (graph.is_connected(cell,world.cells[0]) && !(g[cell].size() == world.connection_pattern.size())){
            int index = map.find(cell.coordinates);
            world.cells[index].occluded = true;
            //cout << "new fake occlusions ...................."<< world.cells[index].coordinates << endl;
            Coordinates c = world.cells[index].coordinates;
            cout << "(" << c.x << "," << c.y << ")" << ",";
        }
    }


//
//    // create new paths
//    Cell_group destination_cg = world.create_cell_group();
//    Graph destination_graph = world.create_graph();
//    Paths paths(destination_graph);
//    auto new_path = paths.get_astar(destination_graph);
//
//    new_path.save("../../cellworld_data/paths/hexagonal." + occlusions  + ".astar");
//    destination_cg.occluded_cells().save("../../cellworld_data/cell_group/hexagonal." + occlusions + ".occlusions");
//
//    cout << "done....." << endl;




    return 0;
}

