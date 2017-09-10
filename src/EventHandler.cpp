#include "EventHandler.h"
EventHandler::EventHandler(Grid* grid)
{
    this->grid = grid;
}

EventHandler::~EventHandler()
{
}

void EventHandler::UpdatePlayers(list<Player*>& players)
{
    list<Cell*> newDeadCellsList;

    for (list<Player*> :: iterator it1 = players.begin(); it1 != players.end(); ++it1)
    {
        Player& player = **it1;
        //lita wszystkich żywych komórek gracza
        list<Cell*> newLivingCells;
        //lista komórek, które w tej iteracji umrą
        list<Cell*> newDeadCells;
        UpdateGrid(player, newLivingCells, newDeadCells);
        //dodajemy martwe komórki gracza do tymczasowej listy
        newDeadCellsList.insert(newDeadCellsList.end(), newDeadCells.begin(), newDeadCells.end());
        player.livingCells = newLivingCells;
    }

    //po ustaleniu komórek wszystkich graczy możemy zgasić zabite komórki wszystkich graczy.
    for (list<Cell*> :: iterator it = newDeadCellsList.begin(); it != newDeadCellsList.end(); ++it)
    {
         Cell& cell = **it;
         cell.UnassignFromPlayer();
    }

    //zapalamy również żywe komórki wszystkich graczy
    for (list<Player*> :: iterator it1 = players.begin(); it1 != players.end(); ++it1)
    {
        Player& player = **it1;
        for (list<Cell*> :: iterator it = player.livingCells.begin(); it != player.livingCells.end(); ++it)
        {
             Cell& cell = **it;
             cell.AssignToPlayer(player.color, player.id);
        }
    }
    //podmieniamy bufor ekranu, tj. sprawiamy że nasze zmiany będą widoczne
    al_flip_display();
}

void EventHandler::UpdateGrid(Player& player, list<Cell*>& newLivingCells, list<Cell*>& newDeadCells)
{
    for (list<Cell*> :: iterator it = player.livingCells.begin(); it != player.livingCells.end(); ++it)
    {
        Cell* cell = *it;
        //może się zdarzyć że ustawiliśmy w edytorze komórkę do innego gracza a poprzedni gracz ma wciąż tę komórkę jako żywą.
        if (cell->id != player.id)
            continue;
        //zaznaczamy, że już tę komórkę sprawdziliśmy
        alreadyProcessed[cell] = true;
        //będziemy zliczać żywych sąsiadów
        int livingNeighbours = 0;
        for (int i = -1 + cell->x; i <= 1 + cell->x; i++)
        {
            int i_index = checkBounds(i, grid->width);
            for (int j = -1 + cell->y; j <= 1 + cell->y; j++)
            {
                //zapewniamy że siatka się zawija
                int j_index = checkBounds(j, grid->height);
                //nie liczymy siebie
                if (i_index == cell->x && j_index == cell->y)
                    continue;
                Cell& neighbour = grid->Cells[i_index][j_index];
                if (neighbour.id == player.id)
                    livingNeighbours++;
                //o ile sąsiad nie należy do rozpatrywanego gracza to sprawdźmy czy ta komórka nie powinna zostać zapalona.
                else
                    checkIfNeedToBeLit(neighbour, newLivingCells, player);
            }
        }
        //wyjmujemy regułę gracza wg. której komórki przeżywają.
        list<int>& currentPlayerToLiveRules = (*(player.currentRules))->toLive;
        //wśród liczb które definiują tę regułę szukamy czy jest faktyczna liczba znalezionych przez metodę żywych komórek
        if (find(currentPlayerToLiveRules.begin(), currentPlayerToLiveRules.end(), livingNeighbours) != currentPlayerToLiveRules.end())
            newLivingCells.push_back(cell);
        else
            newDeadCells.push_back(cell);
    }
    //po przetworzeniu wszystkich komórek gracza czyścimy mapę
    alreadyProcessed.clear();
}

void EventHandler::checkIfNeedToBeLit(Cell& suspected, list<Cell*>& newLivingCells, Player& player)
{
    if (alreadyProcessed[&suspected])
        return;
    alreadyProcessed[&suspected] = true;
    int livingNeighbours = 0;
        for (int i = -1 + suspected.x; i <= 1 + suspected.x; i++)
        {
            //zapewniamy że siatka się zawija
            int i_index = checkBounds(i, grid->width);
            for (int j = -1 + suspected.y; j <= 1 + suspected.y; j++)
            {
                //zapewniamy że siatka się zawija
                int j_index = checkBounds(j, grid->height);
                //nie liczymy siebie
                if (i_index == suspected.x && j_index == suspected.y)
                    continue;
                Cell& neighbour = grid->Cells[i_index][j_index];
                if (neighbour.id == player.id)
                    livingNeighbours++;
            }
        }
        //wyjmujemy regułę gracza wg. której komórki się rodzą.
        list<int>& currentPlayerToBeBornRules = (*(player.currentRules))->toBeBorn;
        //wśród liczb które definiują tę regułę szukamy czy jest faktyczna liczba znalezionych przez metodę żywych komórek
        if (find(currentPlayerToBeBornRules.begin(), currentPlayerToBeBornRules.end(), livingNeighbours) != currentPlayerToBeBornRules.end())
            newLivingCells.push_back(&suspected);
}

int EventHandler::checkBounds(int index, int bound)
{
    index += bound;
    return index % bound;
}

void EventHandler::UpdateCursor(ALLEGRO_MOUSE_STATE& state, Player& player, GUI* gui)
{
    Cell cell = Cell();
    //wyznaczamy nad którą komórką znajduje się kursor
    int x = (state.x - grid->offsetX) / cell.width;
    int y = (state.y - grid->offsetY) / cell.height;

    //interesują nas indeksy komórek tylko tych, które istnieją
    if (x >= 0 && x < grid->width && y >= 0 && y < grid -> height)
    {
        //sprawdzamy czy indeks komórki różni się od poprzedniej pozycji kursora
        if (lastMouseX == x && lastMouseY == y)
            return;
        lastMouseX = x;
        lastMouseY = y;

        //odświeżanie tekstu informującego o obecnie wybranej komórce - tej nad którą jest kursor
        char buf[3];
        itoa(x, buf,10);
        gui->xText = buf;
        char buf1[3];
        itoa(y, buf1,10);
        gui->yText = buf1;
        gui->RefreshTexts();

        //gasimy komórki, które były w liście "highlighted"
        for (list<Cell> :: iterator it = hightlighted.begin(); it != hightlighted.end(); ++it)
        {
            Cell& cell = *it;
            //jeżeli wcześniej komórki należały do innego gracza to zostaną one wyczyszczone.
            grid->Cells[cell.x][cell.y].UnassignFromPlayer();
        }
        hightlighted.clear();

        //dla obecnie wybranego kształtu dodajemy nowe komórki do listy "highlighted" i je zapalamy
        for (list<Cell> :: iterator it = shape->begin(); it != shape->end(); ++it)
        {
            Cell& pattern = *it;
            //zawijamy odpowiednio komórki na gridzie
            int tmp_x = checkBounds(x + pattern.shiftX, grid->width);
            int tmp_y = checkBounds(y + pattern.shiftY, grid->height);
            if (grid->Cells[tmp_x][tmp_y].id != player.id)
            {
                grid->Cells[tmp_x][tmp_y].AssignToPlayer(player.color, player.id);
                //TUTAJ tworzymy kopię komórek z grida, przeciwnie moglibyśmy utracić informację o już zaznaczonych komórkach naszego gracza
                //te kopie dodajemy do listy "highlighted". Komóri z listy mogą sobie spokojnie mrugać a komórki z grida, pamiętają faktyczny stan rozgrywki.
                Cell cell = Cell(grid->Cells[tmp_x][tmp_y]);
                hightlighted.push_front(cell);
                showHighlighted = true;
            }
        }
        al_flip_display();
    }
}


void EventHandler::RemoveHighlighted()
{
    for (list<Cell> :: iterator it = hightlighted.begin(); it != hightlighted.end(); ++it)
    {
        //wyjmujemy komórkę mrugającą z listy "highlighted"
        Cell& cell = *it;
        //na jej podstawie możemy wyjać komórkę z grida, która odpowiada jej co do współrzędnych i tę komórke gasimy
        grid->Cells[cell.x][cell.y].UnassignFromPlayer();
    }
    hightlighted.clear();
    lastMouseX = lastMouseY = -1;
}

void EventHandler::SetNewCells(Player& player)
{
    //lista komórek, które zostaną przypisane do gracza
    list<Cell*> toAssign;
    for (list<Cell> :: iterator it = hightlighted.begin(); it != hightlighted.end(); ++it)
    {
        //wyjmujemy komórkę mrugającą z listy "highlighted"
        Cell& cell = *it;
        //na jej podstawie możemy wyjać komórkę z grida, która odpowiada jej co do współrzędnych
        Cell& toChange = grid->Cells[cell.x][cell.y];
        //przypisujemy komórkę z grida do naszego gracza
        toChange.AssignToPlayer(cell.color, cell.id);
        toAssign.push_back(&toChange);
    }
    //przypisujemy naszemu graczowi komórki z grida, które odpowiadają obecemu mrugającemu kształtowi
    player.AssignCells(toAssign);
    hightlighted.clear();
}


void EventHandler::BlinkHighlighted()
{
    //przechodzimy po liście mrugajacych komórek. Na zmianę - co jedno wywołanie tej metody kolejno zapalamy lub gasimy komórki z "highlighted" uzyskując efekt mrugania.
    for (list<Cell> :: iterator it = hightlighted.begin(); it != hightlighted.end(); ++it)
    {
        Cell& cell = *it;
        int ownerId = cell.id;
        ALLEGRO_COLOR color = cell.color;
        if (!showHighlighted)
        {
           grid->Cells[cell.x][cell.y].UnassignFromPlayer();
        }
        else
        {
           grid->Cells[cell.x][cell.y].AssignToPlayer(color, ownerId);
        }
    }
    showHighlighted = !showHighlighted;
    al_flip_display();
}
