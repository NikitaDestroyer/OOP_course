#include <map>
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<utility>



// поиск по ключу
int filter_key(std::map<std::string,int> mp,std::string search) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        iter++;
        if (search == iter->first)
            return iter->second;
    }
    return NULL;
}

// поиск по значению
std::string filter_value(std::map<std::string, int> mp, int search) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        if (search == iter->second)
            return iter->first;
        iter++;
    }
    return NULL;
}

// вывод  элемнтов мэпа
void out_map(std::map<std::string, int> mp) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        std::cout << iter->first << " " << iter->second<< "\n";
        iter++;
     }
}


// фильтр по предикату
std::map<std::string,int>  filter(std::map<std::string, int> mp, bool (*cmp)(int)) {
    auto iter = mp.begin();
    std::map<std::string,int> result;
    while(iter!=mp.end()) {
        if (cmp(iter->second)) result[iter->first] = iter->second; iter++;
    }
    return result;
}

// search for elements in map, который возвращет вектор различных значений
std::set<int> poisk(std::map<std::string, int> mp) {
    auto iter = mp.begin();
    std::set<int> Set;
    while (iter != mp.end())
        Set.insert(iter->second); iter++;
    return Set;
}

bool test(int value,int threshold = 500) {
    return value > threshold;
}


//Решение задачи 2.1 для класса multimap

int filter_key(std::multimap<std::string, int> mp, std::string search) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        if (search == iter->first)
            return iter->second;
        iter++;
    }
    return NULL;
}

std::string filter_value(std::multimap<std::string, int> mp, int search) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        iter++;
        if (search == iter->second)
            return iter->first;
    }
    return NULL;
}
void out_multimap(std::multimap<std::string, int> mp) {
    auto iter = mp.begin();
    while (iter != mp.end()) {
        std::cout << iter->first << " " << iter->second << "\n";
        iter++;
    }
}


/* WTF
std::multimap< std::string, int>  filter(std::multimap<std::string, int> mp, bool (*cmp)(int)) {
    auto iter = mp.begin(); int c = 0;
    std::multimap<std::string, int>  result;
   
        return result;
    }
}

/*while (iter != mp.end()) {
        if (cmp(iter->second)) {
            c = mp.count(iter->first);
            result.insert(iter, advance(iter, c));
            iter++;
        }
        return result;*/

// search for elements in map
std::set<int> poisk2(std::map<std::string, int> mp) {
    auto iter = mp.begin();
    std::set<int> Set;
    while (iter != mp.end())
        Set.insert(iter->second); iter++;
    return Set;
}

 //функция ведет поиск элемнтов которые имеют одинаковые ключи
std::set<int> find_alt_key(std::multimap<std::string, int> mult,std::string key) {
    std::set<int> Set;
    auto iter = mult.begin();
    while (iter != mult.end()) {
        int c = mult.count(iter->first);
        if (c > 1) {
            Set.insert(iter->second);
            //advance(iter, c); //Если элемнты идет подряд
        }
        iter++;
    }
    return Set;
}
/* WTF
std::multimap< std::string, int>  filter(std::multimap<std::string, int> mp, bool (*cmp)(int)) {
    auto iter = mp.begin(); int c = 0;
    std::multimap<std::string, int>  result;

        return result;
    }
}

/*while (iter != mp.end()) {
        if (cmp(iter->second)) {
            c = mp.count(iter->first);
            result.insert(iter, advance(iter, c));
            iter++;
        }
        return result;*/

        // search for elements in map
int main()
{
    //название производителя,имя модели ,, фамилия имя
    std::map<std::string, std::string> Car;
    /*try {
        //..
        //..equal keys 
    }
    catch{
        exception 
    }
    */
    //for multimap Продемонстрируйте работу контейнера при наличии нескольких элементов с одинаковыми ключами
    std::multimap<std::string, int>  Carr;
    Carr.insert(std::make_pair("first",2));
    Carr.insert(std::make_pair("first",2));
    Carr.insert(std::make_pair("first",3));
    out_multimap(Carr);

}
