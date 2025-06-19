package SimRabbit;

import java.util.ArrayList;
import java.util.List;

public class Map {

    private final int width;
    private final int height;
    
    private final List<Rabbit>[][] grid;

    @SuppressWarnings("unchecked")
    public Map(int width, int height) {
        this.width = width;
        this.height = height;
        this.grid = new ArrayList[width][height];

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                grid[i][j] = new ArrayList<>();
            }
        }
    }

    public boolean addRabbit(int x, int y, Rabbit rabbit) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return false; // Out of bounds
        }
        if (grid[x][y].size() < 5) {
            grid[x][y].add(rabbit);
            return true; // Rabbit added successfully
        }
        return false; // Cell is full
    }

    public int getRabbitCount(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return -1; // Out of bounds
        }
        return grid[x][y].size();
    }

    public void visualizeMap() {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                System.out.print(grid[i][j].size() + " ");
            }
            System.out.println();
        }
    }
}






