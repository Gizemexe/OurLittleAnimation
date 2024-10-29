
#include <windows.h>
#include "icb_gui.h"

//#pragma comment (lib,"winmm.lib")

int F1, F2;
ICBYTES Corridor, Agent, UFO, Cow, Tree, Bird, Dog; 
ICBYTES AgentStanding,DogStanding,TreeStanding,CowStanding; // Karakter ayakta dururken
ICBYTES AgentRunFast[6]; // Hýzlandýrýlmýþ ajan koþma dizisi
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

    // Karakterin durduðu pozisyonu yükleme
    Copy(Agent, 212, 7, 45, 55, AgentStanding);
    PasteNon0(AgentStanding, 600, 450, Corridor);

    // Hýzlý koþma animasyonu
    ICBYTES fastCordinat{ {210, 7, 50, 55}, {113, 8, 75, 55}, {19, 67, 75, 55}, {210, 67, 50, 55}, {113, 67, 75, 55}, {19, 5, 75, 55} };
    for (int i = 0; i < fastCordinat.Y(); i++) {
        Copy(Agent, fastCordinat.I(1, i + 1), fastCordinat.I(2, i + 1), fastCordinat.I(3, i + 1), fastCordinat.I(4, i + 1), AgentRunFast[i]);
    }

    // Ýnek için koordinatlar
    ICBYTES cowCoordinates{ {38, 15, 60, 40}, { 38, 68, 60, 40 } };

    // Ýnek görüntülerini yükleme
    for (int i = 0; i < cowCoordinates.Y(); i++) {
        Copy(Cow, cowCoordinates.I(1, i + 1), cowCoordinates.I(2, i + 1), cowCoordinates.I(3, i + 1), cowCoordinates.I(4, i + 1), CowRun[i]);
    }

    //Kuþ için koordinatlar
    ICBYTES birdCoordinates{ {2, 5, 38, 39}, { 42, 5, 38, 39 }, { 82, 12, 40, 30 },{ 3, 52, 39, 41 } ,{ 43, 55, 39, 28 } ,{ 83, 50, 39, 32 } };

    // Kuþ görüntülerini yükleme
    for (int i = 0; i < birdCoordinates.Y(); i++) {
        Copy(Bird, birdCoordinates.I(1, i + 1), birdCoordinates.I(2, i + 1), birdCoordinates.I(3, i + 1), birdCoordinates.I(4, i + 1), BirdFly[i]);
    }

    //Köpek için koordinatlar
    ICBYTES dogFastCoords{ {10,90,71,32}, {86,89,71,33}, {163,91,75,31} }; // Fast run frames
    for (int i = 0; i < 3; i++) {
        Copy(Dog, dogFastCoords.I(1, i + 1), dogFastCoords.I(2, i + 1), dogFastCoords.I(3, i + 1), dogFastCoords.I(4, i + 1), DogRunFast[i]);
    }

    ICBYTES TV;
    MagnifyX3(Corridor, TV); // Arka planý büyüterek gösterme
    DisplayImage(F1, TV); // Arka plan yüklü
}

void MakeAgentRun(void*) {
    int agentX = 1, agentY = 90;      // Karakterin pozisyonu
    int ufoX = -40, ufoY = 20;        // UFO baþlangýç konumu 
    int cowX = 140, cowY = 103;       // Ýneðin pozisyonu 
    int birdX = 250;                  // Kuþun baþlangýç konumu 
    int birdY = 40;                   // Kuþun Y koordinatý
    int dogX = 25;                    // Köpeðin konumu
    int dogY = 125;
    ICBYTES TV, back;                 // Aðaç için ICBYTES tanýmý
    int fastStep[] = { 6, 6, 6, 6 };  // Koþu adýmlarý
    bool showUFO = false;             // Ufonun görünürlük durumu
    bool cowCaught = false;           // Ýneðin yakalanma durumu
    bool cowDisappear = false;        // Ýneðin görünürlük durumu
    bool birdVisible = false;         // Kuþun görünürlük durumu

    // Arka planý yükle ve ajan baþlangýçta durma pozisyonunda
    ReadImage("touchsome.bmp", Corridor);
    Copy(Corridor, agentX, agentY, 75, 55, back);
    PasteNon0(AgentRunFast[0], agentX, agentY, Corridor); // karakter hýzlý koþma pozisyonunda

    MagnifyX3(Corridor, TV);
    DisplayImage(F1, TV);

    Sleep(500); // Baþlangýçta kýsa bekleme
    PlaySound("scream2.wav", NULL, SND_ASYNC); //Karakter çýðlýðý 

    // Aðaç görüntüsünü yükle
    ReadImage("treee.bmp", Tree); // Aðaç görüntüsünü yükle
    int treeX = 200;               
    int treeY = 2;               

    int i = 0;
    while (true) {
        ReadImage("touchsome.bmp", Corridor); // Arka planý temizle

        // Aðaç görüntüsünü ekrana yerleþtir
        PasteNon0(Tree, treeX, treeY, Corridor);

        // UFO’yu görünür yap
        if (agentX >= cowX - 50 && !showUFO) {
            showUFO = true; 
            
        }     

        // UFO, ajanýn peþinden gelir
        if (showUFO) {
            PasteNon0(UFO, ufoX, ufoY, Corridor); 
            

            // UFO, ineðin üstüne geldiðinde ineði yukarý çeker ve kaybolmasýný saðlar
            if (ufoX >= cowX - 40 && ufoX < cowX + 40 && !cowCaught) {
                cowCaught = true; // Ýnek yakalandý
                PlaySound("cowww.wav", NULL, SND_ASYNC); //Ýneðin sesi
                
            }

            // UFO'nun Y koordinatýný sabit tut
            if (cowCaught) {
                ufoY = 20; // UFO'nun Y pozisyonunu sabit tut
            }
            else {

                ufoX += 5; // UFO saða doðru hareket eder
            }

            // Kuþun görünürlüðünü kontrol et
            if (!birdVisible) {
                birdVisible = true; 
                PlaySound("birdd.wav", NULL, SND_ASYNC); //kuþ sesi
            }
        }

        // Kuþu ekrana yerleþtir ve hareket ettir
        if (birdVisible) {
            PasteNon0(BirdFly[i / 10 % 6], birdX, birdY, Corridor); // Kuþ animasyonu
            birdX -= 15; 
            birdY -= 2;  
        }

        // Ýnek animasyonu
        if (!cowCaught && !cowDisappear) {
            PasteNon0(CowRun[(i / 10) % 2], cowX, cowY, Corridor); 
        }
        
        // Ýnek yakalanýnca yukarý hareket 
        if (cowCaught && !cowDisappear) {
            cowY -= 10; // Ýneði yukarý doðru hareket ettir
            PasteNon0(CowRun[0], cowX, cowY, Corridor);

            if (cowY < ufoY + 20) { // UFO’ya ulaþtýðýnda kaybolur
                cowDisappear = true;
                PlaySound("flyUfoo.wav", NULL, SND_ASYNC);  // Ufo sesi
            }
        }

        // Ajanýn hýzlý koþma animasyonu
        PasteNon0(AgentRunFast[i % 6], agentX, agentY, Corridor);
        agentX += fastStep[i % 4]; 

        //Köpeðin hýzlý koþma animasyonu
        PasteNon0(DogRunFast[i % 3], dogX, dogY, Corridor);
        dogX += fastStep[i % 4];

        // UFO, ineðin yukarý hareketi sýrasýnda bekle
        if (cowDisappear) {
            ufoX += 10; // UFO saða hýzlanarak gider
            if (ufoX > 400) break; // Ekrandan tamamen çýktýðýnda döngü biter
        }

        // Ekraný güncelle
        MagnifyX3(Corridor, TV);
        DisplayImage(F1, TV);
        Sleep(40); // Animasyon hýzýný kontrol eder

        i++; // Çerçeve sayýsýný artýr
    }
}

void ICGUI_main() {
    F1 = ICG_FrameThin(5, 140, 450, 430);
    F2 = ICG_FrameThin(5, 5, 20, 20);
    ICG_Button(400, 5, 160, 55, "Load the Animation\n1 -----------------------------------\n Animasyonu Yükle", LoadAgentRun);
    ICG_TButton(580, 5, 160, 55, "Start the Animation\n2 -----------------------------------\n Animasyonu Baþlat", MakeAgentRun, NULL);
    ReadImage("touchsome.bmp", Corridor);
    DisplayImage(F1, Corridor);
    ReadImage("53632678.bmp", Agent);
    DisplayImage(F2, Agent);
}