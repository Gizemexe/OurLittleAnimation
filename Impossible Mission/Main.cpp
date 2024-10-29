
#include <windows.h>
#include "icb_gui.h"

//#pragma comment (lib,"winmm.lib")

int F1, F2;
ICBYTES Corridor, Agent, UFO, Cow, Tree, Bird, Dog; 
ICBYTES AgentStanding,DogStanding,TreeStanding,CowStanding; // Karakter ayakta dururken
ICBYTES AgentRunFast[6]; // H�zland�r�lm�� ajan ko�ma dizisi
ICBYTES DogRunFast[3];
ICBYTES CowRun[2];
ICBYTES BirdFly[6];

void ICGUI_Create() {
    ICG_MWSize(1200, 830);
    ICG_MWTitle("Our Little Animation");
}

void LoadAgentRun() {
    ReadImage("touchsome.bmp", Corridor);
    ReadImage("pixilUfo.bmp", UFO); 
    ReadImage("xyy.bmp", Cow);
    ReadImage("Treee.bmp", Tree);
    ReadImage("birds.bmp", Bird);
    ReadImage("dogg.bmp", Dog);

    // Karakterin durdu�u pozisyonu y�kleme
    Copy(Agent, 212, 7, 45, 55, AgentStanding);
    PasteNon0(AgentStanding, 600, 450, Corridor);

    // H�zl� ko�ma animasyonu
    ICBYTES fastCordinat{ {210, 7, 50, 55}, {113, 8, 75, 55}, {19, 67, 75, 55}, {210, 67, 50, 55}, {113, 67, 75, 55}, {19, 5, 75, 55} };
    for (int i = 0; i < fastCordinat.Y(); i++) {
        Copy(Agent, fastCordinat.I(1, i + 1), fastCordinat.I(2, i + 1), fastCordinat.I(3, i + 1), fastCordinat.I(4, i + 1), AgentRunFast[i]);
    }

    // �nek i�in koordinatlar
    ICBYTES cowCoordinates{ {38, 15, 60, 40}, { 38, 68, 60, 40 } };

    // �nek g�r�nt�lerini y�kleme
    for (int i = 0; i < cowCoordinates.Y(); i++) {
        Copy(Cow, cowCoordinates.I(1, i + 1), cowCoordinates.I(2, i + 1), cowCoordinates.I(3, i + 1), cowCoordinates.I(4, i + 1), CowRun[i]);
    }

    //Ku� i�in koordinatlar
    ICBYTES birdCoordinates{ {2, 5, 38, 39}, { 42, 5, 38, 39 }, { 82, 12, 40, 30 },{ 3, 52, 39, 41 } ,{ 43, 55, 39, 28 } ,{ 83, 50, 39, 32 } };

    // Ku� g�r�nt�lerini y�kleme
    for (int i = 0; i < birdCoordinates.Y(); i++) {
        Copy(Bird, birdCoordinates.I(1, i + 1), birdCoordinates.I(2, i + 1), birdCoordinates.I(3, i + 1), birdCoordinates.I(4, i + 1), BirdFly[i]);
    }

    //K�pek i�in koordinatlar
    ICBYTES dogFastCoords{ {10,90,71,32}, {86,89,71,33}, {163,91,75,31} }; // Fast run frames
    for (int i = 0; i < 3; i++) {
        Copy(Dog, dogFastCoords.I(1, i + 1), dogFastCoords.I(2, i + 1), dogFastCoords.I(3, i + 1), dogFastCoords.I(4, i + 1), DogRunFast[i]);
    }

    ICBYTES TV;
    MagnifyX3(Corridor, TV); // Arka plan� b�y�terek g�sterme
    DisplayImage(F1, TV); // Arka plan y�kl�
}

void MakeAgentRun(void*) {
    int agentX = 1, agentY = 90;      // Karakterin pozisyonu
    int ufoX = -40, ufoY = 20;        // UFO ba�lang�� konumu 
    int cowX = 140, cowY = 103;       // �ne�in pozisyonu 
    int birdX = 250;                  // Ku�un ba�lang�� konumu 
    int birdY = 40;                   // Ku�un Y koordinat�
    int dogX = 25;                    // K�pe�in konumu
    int dogY = 125;
    ICBYTES TV, back;                 // A�a� i�in ICBYTES tan�m�
    int fastStep[] = { 6, 6, 6, 6 };  // Ko�u ad�mlar�
    bool showUFO = false;             // Ufonun g�r�n�rl�k durumu
    bool cowCaught = false;           // �ne�in yakalanma durumu
    bool cowDisappear = false;        // �ne�in g�r�n�rl�k durumu
    bool birdVisible = false;         // Ku�un g�r�n�rl�k durumu

    // Arka plan� y�kle ve ajan ba�lang��ta durma pozisyonunda
    ReadImage("touchsome.bmp", Corridor);
    Copy(Corridor, agentX, agentY, 75, 55, back);
    PasteNon0(AgentRunFast[0], agentX, agentY, Corridor); // karakter h�zl� ko�ma pozisyonunda

    MagnifyX3(Corridor, TV);
    DisplayImage(F1, TV);

    Sleep(500); // Ba�lang��ta k�sa bekleme
    PlaySound("scream2.wav", NULL, SND_ASYNC); //Karakter ���l��� 

    // A�a� g�r�nt�s�n� y�kle
    ReadImage("treee.bmp", Tree); // A�a� g�r�nt�s�n� y�kle
    int treeX = 200;               
    int treeY = 2;               

    int i = 0;
    while (true) {
        ReadImage("touchsome.bmp", Corridor); // Arka plan� temizle

        // A�a� g�r�nt�s�n� ekrana yerle�tir
        PasteNon0(Tree, treeX, treeY, Corridor);

        // UFO�yu g�r�n�r yap
        if (agentX >= cowX - 50 && !showUFO) {
            showUFO = true; 
            
        }     

        // UFO, ajan�n pe�inden gelir
        if (showUFO) {
            PasteNon0(UFO, ufoX, ufoY, Corridor); 
            

            // UFO, ine�in �st�ne geldi�inde ine�i yukar� �eker ve kaybolmas�n� sa�lar
            if (ufoX >= cowX - 40 && ufoX < cowX + 40 && !cowCaught) {
                cowCaught = true; // �nek yakaland�
                PlaySound("cowww.wav", NULL, SND_ASYNC); //�ne�in sesi
                
            }

            // UFO'nun Y koordinat�n� sabit tut
            if (cowCaught) {
                ufoY = 20; // UFO'nun Y pozisyonunu sabit tut
            }
            else {

                ufoX += 5; // UFO sa�a do�ru hareket eder
            }

            // Ku�un g�r�n�rl���n� kontrol et
            if (!birdVisible) {
                birdVisible = true; 
                PlaySound("birdd.wav", NULL, SND_ASYNC); //ku� sesi
            }
        }

        // Ku�u ekrana yerle�tir ve hareket ettir
        if (birdVisible) {
            PasteNon0(BirdFly[i / 10 % 6], birdX, birdY, Corridor); // Ku� animasyonu
            birdX -= 15; 
            birdY -= 2;  
        }

        // �nek animasyonu
        if (!cowCaught && !cowDisappear) {
            PasteNon0(CowRun[(i / 10) % 2], cowX, cowY, Corridor); 
        }
        
        // �nek yakalan�nca yukar� hareket 
        if (cowCaught && !cowDisappear) {
            cowY -= 10; // �ne�i yukar� do�ru hareket ettir
            PasteNon0(CowRun[0], cowX, cowY, Corridor);

            if (cowY < ufoY + 20) { // UFO�ya ula�t���nda kaybolur
                cowDisappear = true;
                PlaySound("flyUfoo.wav", NULL, SND_ASYNC);  // Ufo sesi
            }
        }

        // Ajan�n h�zl� ko�ma animasyonu
        PasteNon0(AgentRunFast[i % 6], agentX, agentY, Corridor);
        agentX += fastStep[i % 4]; 

        //K�pe�in h�zl� ko�ma animasyonu
        PasteNon0(DogRunFast[i % 3], dogX, dogY, Corridor);
        dogX += fastStep[i % 4];

        // UFO, ine�in yukar� hareketi s�ras�nda bekle
        if (cowDisappear) {
            ufoX += 10; // UFO sa�a h�zlanarak gider
            if (ufoX > 400) break; // Ekrandan tamamen ��kt���nda d�ng� biter
        }

        // Ekran� g�ncelle
        MagnifyX3(Corridor, TV);
        DisplayImage(F1, TV);
        Sleep(40); // Animasyon h�z�n� kontrol eder

        i++; // �er�eve say�s�n� art�r
    }
}

void ICGUI_main() {
    F1 = ICG_FrameThin(5, 140, 450, 430);
    F2 = ICG_FrameThin(5, 5, 20, 20);
    ICG_Button(400, 5, 160, 55, "Load the Animation\n1 -----------------------------------\n Animasyonu Y�kle", LoadAgentRun);
    ICG_TButton(580, 5, 160, 55, "Start the Animation\n2 -----------------------------------\n Animasyonu Ba�lat", MakeAgentRun, NULL);
    ReadImage("touchsome.bmp", Corridor);
    DisplayImage(F1, Corridor);
    ReadImage("53632678.bmp", Agent);
    DisplayImage(F2, Agent);
}