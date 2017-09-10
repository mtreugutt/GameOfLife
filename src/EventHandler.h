#pragma once
#include "Grid.h"
#include "Player.h"
#include "Rules.h"
#include "GUI.h"
#include <algorithm>
#include <list>
#include <map>
using namespace std;

//klasa obsługuje requesty zgłaszane przez "EventListener", zawiera logikę rozgrywki
class EventHandler
{
    public:
        //konstruktor przyjmujący siatkę komórek
        EventHandler(Grid* grid);
        ~EventHandler();
        //Uaktualnienie siatki rozgrywki na podstawie komórek podanego gracza. Metoda uzupełnia listę jego żyjących i umierających komórek.
        void UpdateGrid(Player& player, list<Cell*>& newLivingCells, list<Cell*>& newDeadCells);
        //Metoda uaktualnia komórki wszystkich graczy, woła dla każdego gracza metodę "Update Grid". Przetrzymuje listę martwych komórek wszystkich graczy.
        //Po przeprocesowaniu wszystkich graczy usuwa gasi wszystkie martwe komórki. Potem przechodzi po wszystkich graczach i zapala ich żywe komórki
        void UpdatePlayers(list<Player*>& players);
        //Metoda służy uaktualnieniu zachowania komórek pod którymi znalazł się kursor na podstawie obecnie wybranego kształtu. Metoda na początku sprawdza czy kursor zmienił swoją
        //pozycję względem ostatniego wywołania. Jeżeli tak to gasi dotychczasowe mrugające komórki, tj. te które znajdują się w liście "highlighted". Jeżeli mrugające komórki
        //przykryły komórki innego gracza to komórki innego gracza zostaną zgaszone. Następnie dodaje do listy highlighted nowe mrugające komórki i je zapala.
        void UpdateCursor(ALLEGRO_MOUSE_STATE& state, Player& player, GUI* gui);
        //Metoda kolejno zapala lub gasi komórki z listy "highlighted"
        void BlinkHighlighted();
        //Gasi komórki będące na liście "highlighted", pozwala wrócić do symulacji.
        void RemoveHighlighted();
        //Pozwala przypisać do gracza i zapalić komórki
        void SetNewCells(Player& player);
        //wskaŸnik do grida, który trzyma wszystkie komórki
        Grid* grid;
        //wskaŸnik do obecnie wybranego kształtu. Jest on ustawiany bezpośrednio przez klasę EventListener
        list<Cell>* shape;
    private:
        //mapa przetworzonych komórek. Nie ma sensu kilkakrotnie sprawdzać sąsiedztwa tej samej komórki. Chcemy to robić tylko raz.
        map<Cell*, bool> alreadyProcessed;
        //lista mrugających komórek, tych które gracz może zazanczyć jako swoje
        list<Cell> hightlighted;
        //metoda sprawdza sąsiedztwo komórki "suspected" gracza "player". W razie potrzeby dodaje "suspected" do listy żywych komórek "newLivigCells"
        void checkIfNeedToBeLit(Cell& suspected, list<Cell*>& newLivingCells, Player& player);
        //metoda zawija współrzędną index tak by zawsze była z zakresu [0; "bound"]
        int checkBounds(int index, int bound);
        //flaga informująca czy należy zapalić czy zgasić komórki
        bool showHighlighted;
        //współrzędne komórki nad którą znajdywał się kursor w poprzedniej klatce (poprzednim wywołaniu)
        int lastMouseX, lastMouseY;
};
