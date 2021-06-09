#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <memory>
#include "plane.hpp"
#include "pyramid.hpp"
#include "triangular.hpp"
#include "circus.hpp"
#include "tent.hpp"
#include "volcano.hpp"
#include "drone.hpp"
#include "lacze_do_gnuplota.hpp"

constexpr unsigned int SIZE = 2;
constexpr char file_extension[] = ".dat";
/*!
 * \file  scene.hpp
 *  
 *  \brief Plik zawiera definicję klasy reprezentujacej scene,
 *         obslugujacej zapis do plikow i wytswietlanie w gnuplocie
 */

/*!
 *  \class Scene
 *  \brief Opisuje scene w 3D w ktorej poruszaja sie drony
 */
class Scene
{
private:
  /*!
 * \brief Tablica dronow obslugiwanych w programie
 */
  Drone flies[SIZE];
  /*!
 * \brief Wskaznik na aktywnego drona. Wartosc koresponduje z ta
 *          z tablicy flies (drony sa numerowane w zakresie 0 , 1 , ... , (SIZE-1))
 */

  unsigned int active;

  /*!
 * \brief Lista wskaznikow na obiekty sceny (klasy Block)
 *          Bedzie reprezentowala listy przeszkod rysowanych na powierzchni w gnuplocie
 */
  std::list<std::shared_ptr<Block>> objects;

  /*!
 * \brief Zmienna zapamietujaca liczbe stworzonych obiektow, uzywana przy dopisywania plikow
 */
  unsigned int filename_num;

public:
  /*!
 * \brief Konstruktor paramereyczny klasy Scene
 *      \param[in] pos - tablica polozen dronow
 *      \param[in] scal_bod - tablica skali korpusow dronow
 *      \param[in] scal_rot - tablica skali rotorow dronow
 *      \param[in] names_bod - tablica nazw plikow sample i final dla prostopadloscianow body
 *      \param[in] names_rot - tablica nazw plikow sample i final dla graniastoslupow rotors
 *      \post Ustawia odpowiednie wartosci klasy, zadane przez uzytkownika
 */
  Scene(Vector3D const (&pos)[SIZE], Vector3D const (&scal_bod)[SIZE], Vector3D const (&scal_rot)[SIZE],
        std::string const (&names_bod)[SIZE][2], std::string const (&names_rot)[SIZE][4][2]);

  /*!
 * \brief Metoda inicjujaca liste objects, dodajaca drony do listy
 *      \retval true - objects poprawnie zainicjowana
 *      \retval false - objects blednie zainicjowana
 */
  bool init_objects();

  /*!
 * \brief Metoda dodajaca podstawowe elementy do listy objects
 * \retval True lub False w zaleznosci od tego czy operacja sie powiedzie
 */
  bool add_basic_objects();

  /*!
 * \brief Metoda dodajaca object zadany przez uzytkownika
 *      \param[in] sca - docelowo scale z klasy Block 
 *      \param[in] x - skladowa x translacji
 *      \param[in] y - skladowa y translacji
 *      \param[in] angle - kat obrotu wokol osi z wprowadzanej figury
 *      \param[in] option - decyduje jaki typ figury ( 1 - Pyramid, 2 - Triangular, 3 - Cuboid) utworzyc
 *      \param[in] Lacze - aktywne lacze do Gnuplota
 * \post Tworzy figure o zadanych parametrach i ja skaluje, po czym przesuwana jest w zadane (przez x,y) miejsce
 * \retval False - gdy wprowadzona zostanie bledna option, True - w przeciwnym wypadku
 */
  bool add_object(const Vector3D &sca, const double &x, const double &y, const double &angle, const unsigned int &option, PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Metoda usuwajaca object zadany przez uzytkownika
 *      \param[in] num - decyduje ktora figure usunac z zakresu (3-liczba obiektow) nie mozna usunac drona
 *      \param[in] Lacze - aktywne lacze do Gnuplota
 * \post Usuwa z listy pewna figure
 * \retval False - gdy wprowadzona zostanie bledny num, True - w przeciwnym wypadku
 */
  bool delete_object(const unsigned int &num, PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Metoda zmieniajaca pozycje wybranego przez uzytkownika elementu sceny
 *      \param[in] num - decyduje ktora figure usunac z zakresu (3-liczba obiektow) nie mozna usunac drona
 *      \param[in] x - nowa pozycja x figury
 *      \param[in] y - nowa pozycja y figury
 * \post Usuwa z listy pewna figure
 * \retval False - gdy wprowadzona zostanie bledny num, True - w przeciwnym wypadku
 */
  bool switch_object_position(const unsigned int &num, const double &x, const double &y);

  /*!
 * \brief Metoda dodajaca prostopadloscian, ostroslup lub Triangular do listy objects
 *      \param[in] s_name - docelowo sample_name z klasy Block
 *      \param[in] f_name - docelowo final_name z klasy Block
 *      \param[in] sca - docelowo scale z klasy Block 
 *      \param[in] x - skladowa x translacji
 *      \param[in] y - skladowa y translacji
 *      \param[in] angle - kat obrotu wokol osi z wprowadzanej figury
 *      \param[in] option - decyduje jaki typ figury ( 1 - Pyramid, 2 - Triangular, 3 - Cuboid) utworzyc
 * \post Tworzy figure o zadanych parametrach i ja skaluje, po czym przesuwana jest w zadane (przez x,y) miejsce
 * \retval False - gdy wprowadzona zostanie bledna option, True - w przeciwnym przypadku
 */
  bool add_object_type_cuboid(const std::string &s_name, const std::string &f_name, const Vector3D &sca,
                              const double &x, const double &y, const double &angle, const unsigned int &option);

  /*!
 * \brief Metoda dodajaca obiekt pochodny z Prism do listy objects
 *      \param[in] s_name - docelowo sample_name z klasy Block
 *      \param[in] f_name - docelowo final_name z klasy Block
 *      \param[in] sca - docelowo scale z klasy Block 
 *      \param[in] x - skladowa x translacji
 *      \param[in] y - skladowa y translacji
 *      \param[in] angle - kat obrotu wokol osi z wprowadzanej figury
 *      \param[in] option - decyduje jaki typ figury ( 4 - Circus, 5 - Tent, 6 - Volcano) utworzyc
 * \post Tworzy figure o zadanych parametrach i ja skaluje, po czym przesuwana jest w zadane (przez x,y) miejsce
 * \retval False - gdy wprowadzona zostanie bledna option, True - w przeciwnym przypadku
 */
  bool add_object_type_prism(const std::string &s_name, const std::string &f_name, const Vector3D &sca,
                             const double &x, const double &y, const double &angle, const unsigned int &option);

  /*!
 * \brief Metoda tworzaca nazwy programow, uzywana przy dodawaniu obiektow sceny
 *     \pre s_name i f_name musza byc pustymi stringami
 *     \param[in] s_name - docelowo sample name      
 *     \param[in] f_name - docelowo final_name       
 *     \param[in] option - w zaleznosci od opcji (dzialajacej analogicznie jak w metodzie
 *                         add_objects_type_cuboid()) odpowiednia nazwa pliku sie utworzy                                                                   
 *     \post Przypisuje nazwy do s_name, f_name         
 *     \retval true lub false, w zaleznosci od warunku pre oraz czy podano poprawna opcje                        
 */
  bool create_filenames(std::string &s_name, std::string &f_name, const unsigned int &option);

  /*!
 * \brief Metoda uzywana w switchu metody create_filenames. Sluzy do tworzenia pliku o odpowiedniej nazwie
 *        \param[in] type - typ zapisywany do nazwy
 */
  void switch_create_filenames(std::string &s_name, std::string &f_name, const std::string &type);

  /*!
 * \brief Metoda sprawdzajaca i zwracajaca rozmiar listy objects
 *      \return objects.size()
 */
  int get_objects_size() const;

  /*!
 * \brief Metoda sprawdzajaca poprawnosc inicjacji sceny
 *      \retval true - scena poprawnie zainicjowana
 *      \retval false - scena blednie zainicjowana
 */
  bool check_scene();

  /*!
 *  \brief Przeciazenie operatora == dla klasy Scene    
 *       \b{Parametr active jest pomijany}                                         
 *      \param[in] pri - porownywana scena                                            
 *      \retval false - nie sa rowne, 
 *      \retval true - sa rowne                                                     
 */
  bool operator==(const Scene &sce) const;

  /*!
 * \brief Metoda pozwalajaca na wybor aktywnego drona
 *      \param[in] ch - nowo wybrany dron
 *      \post Wybiera aktywnego drona (wartosc klasy active)
 *      \retval false - jesli zadana wartosc jest spoza zakresu
 *      \retval true - jesli zadana wartosc jest poprawna
 */
  bool choose_drone(unsigned int const &ch);

  /*!
 * \brief Metoda inicjalizujaca lacze do gnuplota
 *  \param[in] parametry okreslajace zakresy
 *  \param[in] Lacze - inicjowane LaczeDoGNUPlota
 *  \post Powstaje w pelni skonfigurowane lacze, ktore 
 *          moze byc uzyte do rysowania calej sceny
 *  \retval true - jesli operacja sie powiedzie
 *  \retval false - w przeciwnym wypadku
 */
  bool init_gnuplot(double const &x, double const &y, PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Metoda iterujaca po kolejnych polach listy objects,
 *          zcyztujaca nazwy plikow i podajaca je do gnuplota
 *  \param[in] Lacze - aktywne LaczeDoGNUPlota
 *  \post Do Lacza trafiaja kolejne nazwy plikow
 *  \retval true - jesli operacja sie powiedzie
 *  \retval false - w przeciwnym wypadku
 */
  bool iterate_over_objects(PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Zwraca numer aktywnego drona
 */
  unsigned int get_active() const;

  /*!
 * \brief Zwraca liczbe stworzonych plikow filename_num
 */
  unsigned int get_filename_num() const;

  /*!
 * \brief Wypisuje polozenie aktywnego drona
 */
  void print_active() const;

  /*!
 * \brief Wypisuje polozenia dronow
 */
  void print_positions() const;

  /*!
 * \brief Przelot aktywnego drona
  *     \pre Lacze musi byc odpowiednio skonfigurowane
 *     \param[in] angle - kat w stopniach
 *     \param[in] len - dlugosc przelotu       
 *     \param[in] Lacze - aktywne lacze do gnuplota                                                                          
 *     \post W oknie gnuplota wykonuje sie animacja translacji drona
 *     \retval true - jesli jest odpowiednio skonfigurowane lacze
 *     \retval false - w przeciwnym wypadku                                   
 */

  bool fly(double const &angle, double const &len, PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Przelot aktywnego drona
  *     \pre Lacze musi byc odpowiednio skonfigurowane
 *     \param[in] radius - promien okregu przelotu      
 *     \param[in] Lacze - aktywne lacze do gnuplota                                                                          
 *     \post W oknie gnuplota wykonuje sie animacja translacji drona  
 *     \retval true - jesli jest odpowiednio skonfigurowane lacze
 *     \retval false - w przeciwnym wypadku                                 
 */
  bool fly_roundabout(double const &radius, PzG::LaczeDoGNUPlota &Lacze);

  /*!
 * \brief Wyswietla aktywne elementy sceny wyboru obiektu
 */
  void show_elements();
};