
#include <stdio.h>
#include <stdlib.h>
/* заголовочный файл для работы с динамическими библиотеками */
#include <dlfcn.h>

int main(int argc, char* argv[]){
	void *ext_library;	// хандлер внешней библиотеки
	double value=0;		// значение для теста
    double value2=0;		// значение для теста
	double (*powerfunc)(double x , double y);	// переменная для хранения адреса функции

	//загрузка библиотеки
	ext_library = dlopen("/home/vanguard/eltexC/module5/eltexmodule5/task6/dynamic2/libpowers.so",RTLD_LAZY);
	if (!ext_library){
		//если ошибка, то вывести ее на экран
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		return 1;
	};

	//загружаем из библиотеки требуемую процедуру
	powerfunc = dlsym(ext_library, argv[1]);
	value=atoi(argv[2]);
    value2=atoi(argv[3]);

	//выводим результат работы процедуры
	printf("%s(%.0f %.0f) = %f\n",argv[1],value,value2,(*powerfunc)(value , value2));

	//закрываем библиотеку
	dlclose(ext_library);

	return 0;
};


//ext_library = dlopen("/home/vanguard/eltexC/module5/eltexmodule5/task6/dynamic2/libpowers.so",RTLD_LAZY);