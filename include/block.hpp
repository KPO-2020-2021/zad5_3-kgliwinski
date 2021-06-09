#pragma once
#include <string>
#include <fstream>
#include "vector3D.hpp"
#include "matrix3D.hpp"

/*!
 * \file  block.hpp
 *  
 *  \brief Plik zawiera definicję klasy reprezentujacej bryle
 *  w przestrzeni trojwymiarowej
 */

/*!
 *  \class Block
 *  \brief Opisuje figure geometryczna w przestrzeni trojwymiarowej
 */
class Block
{
    protected:
    
/*!
 * \brief Nazwa pliku z wzorcowym opisem figury
 */
    std::string sample_name;
    
/*!
 * \brief Nazwa pliku z roboczym opisem figury
 */    
    std::string final_name;
/*!
 * \brief Vector3D ze skala dla danej fihury
 */
    Vector3D scale;
    
    public:

/*!
 * \brief Konstruktor bezparamereyczny klasy Block
 *          Ustawia sample_name i final_name na NULL oraz
 *          Vector3D scale na [1,1,1] (aby nie zmienial skali)
 */  
    Block();
/*!
 * \brief Konstruktor paramereyczny klasy Block
 *      \param[in] s_name - docelowo sample_name z klasy Block
 *      \param[in] f_name - docelowo final_name z klasy Block
 *      \param[in] vec - docelowo scale z klasy Block
 *      \post Ustawia nazwy na odpowiednie podane przez uzytkownika
 */
    Block(const std::string &s_name, const std::string &f_name, const Vector3D &vec);

    /*!
 * \brief Konstruktor paramereyczny klasy Block
 *      \param[in] s_name - docelowo sample_name z klasy Block
 *      \param[in] f_name - docelowo final_name z klasy Block
 *      \post Ustawia nazwy na odpowiednie podane przez uzytkownika, skala jest ustawiana
 *             na [1,1,1]
 */
    Block(const std::string &s_name, const std::string &f_name);

/*!
 *  \brief Metoda zapisujaca do klasy nazwe pliku z wzorcowa bryla                                                                                                    
 *      \param[in] name - nazwa pliku                                                                                                                 
 *     \post Zmiana sample_name na ta podana przez uzytkownika                               
 */
    void set_sample_name(const std::string &name);

/*!
 *  \brief Metoda zapisujaca do klasy nazwe pliku z finalna (robocza) bryla                                                                                                      
 *      \param[in] name - nazwa pliku                                                                                                                 
 *     \post Zmiana final_name na ta podana przez uzytkownika                                
 */
    void set_final_name(const std::string &name);

/*!
 *  \brief Metoda zapisujaca do klasy wektor reprezentujacy skale                                                                                                     
 *      \param[in] vec - Vector3D zawierajacy skale                                                                                                               
 *     \post Zmiana skali na te podana przez uzytkownika                                
 */
    void set_scale(const Vector3D &vec);

/*!
 *  \brief Metoda zapisujaca do klasy wektor reprezentujacy skale                                                                                                       
 *      \param[in] tab - tablica z ktorej powstanie wektor                                                                                                         
 *     \post Zmiana skali na te podana przez uzytkownika                                
 */
    void set_scale(double (&tab)[3]);

    /*!
 *  \brief Metoda sprawdzajaca Block 
 *     \pre nazwy plikow nie moga byc puste, skala musi byc dodatnia                                                                                                                                                                                                    
 *     \retval true - jesli poprawne
 *     \retval false - w przeciwnym wypadku                               
 */
    bool check_block() const;
    

/*!
 *  \brief Metoda zwracajaca nazwe pliku z wzorcowa bryla                                                                                              
 *                                                                        
 *     \return Zwraca nazwe pliku                              
 */
    std::string get_sample_name() const;

/*!
 *  \brief Metoda zwracajaca nazwe pliku z finalna (robocza) bryla                                                                                               
 *                                                                        
 *     \return Zwraca nazwe pliku                              
 */
    std::string get_final_name() const;

/*!
 *  \brief Metoda zapisujaca do klasy wektor reprezentujacy skale                                                             
 *     \post Zmiana skali na te podana przez uzytkownika                                
 */
    Vector3D get_scale() const;

   /*!
 *  \brief Zwraca nazwe obiektu                                                    
 */
virtual void print_name() const;

   /*!
 *  \brief Zwraca pozycje obiektu                                                    
 */
virtual void print_pos() const;

   /*!
 *  \brief Zwraca pozycje obiektu do Vector3D                                                    
 */
virtual Vector3D get_pos() const;

   /*!
 *  \brief Zmiana pozycji obiektu                                                   
 */
virtual void switch_pos(const double &x, const double &y);
};