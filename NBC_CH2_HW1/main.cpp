
#include <iostream>
#include <string>
using namespace std;

enum class ESTAT {
    HP, MP, DAMAGE, ARMOR, STR, DEX, INT, CNT
};
enum class ECLASS {
    WARRIOR, ROGUE, MAGE, CNT
};

const string eclass_to_string[static_cast<int>(ECLASS::CNT)] = {
     "WARRIOR", "ROGUE", "MAGE"
};

const int primary_stat_idx[static_cast<int>(ECLASS::CNT)] = {
    static_cast<int>(ESTAT::STR),
    static_cast<int>(ESTAT::DEX),
    static_cast<int>(ESTAT::INT)
};

void setPotion(int count, int* p_HPPotion, int* p_MPPotion);
void levelUp(int* p_level, int* status, ECLASS char_class, int* p_HPPotion, int* p_MPPotion);


int main() {
    ECLASS char_class;
    int status[static_cast<int>(ESTAT::CNT)] = { 0, };
    int nr_HPPotion = 0, nr_MPPotion = 0;
    int level = 1;
    int cmd = -1;


    status[static_cast<int>(ESTAT::STR)] = 1;
    status[static_cast<int>(ESTAT::DEX)] = 1;
    status[static_cast<int>(ESTAT::INT)] = 1;


    for (;;) {
        for (int i = 0; i < static_cast<int>(ECLASS::CNT); ++i) {
            cout << i << ". " << eclass_to_string[i] << endl;
        }
        cout << "직업을 선택하세요: ";
        cin >> cmd;
        if (cmd < 0 || cmd>2) {
            cout << "다시 입력하세요" << endl;
            continue;
        }
        char_class = static_cast<ECLASS>(cmd);
        break;
    }


    for (;;) {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> status[static_cast<int>(ESTAT::HP)] >> status[static_cast<int>(ESTAT::MP)];
        if (!(status[static_cast<int>(ESTAT::HP)] <= 50 || status[static_cast<int>(ESTAT::MP)] <= 50))
            break;
        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    for (;;) {
        cout << "공격력과 방어력를 입력해주세요: ";
        cin >> status[static_cast<int>(ESTAT::DAMAGE)] >> status[static_cast<int>(ESTAT::ARMOR)];
        if (!(status[static_cast<int>(ESTAT::DAMAGE)] <= 0 || status[static_cast<int>(ESTAT::ARMOR)] <= 0))
            break;
        cout << "공격력과 방어력의 값이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    setPotion(5, &nr_HPPotion, &nr_MPPotion);
    cout << " * 포션이 지급되었습니다. (HP, MP 포션 각 5개)" << endl;
    cout << "=============================================\
            \n< 스탯 관리 시스템 >\
            \n1. HP UP\
            \n2. MP UP\
            \n3. 공격력 UP\
            \n4. 방어력 UP\
            \n5. 현재 능력치\
            \n6. Level UP\
            \n0. 나가기\n";

    cmd = -1;
    while (cmd) {
        cout << "번호를 선택해주세요: ";
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            if (nr_HPPotion > 0) {
                status[static_cast<int>(ESTAT::HP)] += 20;
                --nr_HPPotion;
                cout << "* HP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
                cout << "현재 HP: " << status[static_cast<int>(ESTAT::HP)] <<
                    "\n남은 포션 수: " << nr_HPPotion << endl;
            }
            else {
                cout << "포션이 부족합니다." << endl;
            }
            break;
        case 2:
            if (nr_MPPotion > 0) {
                status[static_cast<int>(ESTAT::MP)] += 20;
                --nr_MPPotion;
                cout << "* MP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
                cout << "현재 MP: " << status[static_cast<int>(ESTAT::MP)] <<
                    "\n남은 포션 수: " << nr_MPPotion << endl;
            }
            else {
                cout << "포션이 부족합니다." << endl;
            }

            break;
        case 3:
            status[static_cast<int>(ESTAT::DAMAGE)] *= 2;;
            cout << " * 공격력이 2배로 증가되었습니다.\
                \n현재 공격력: " << status[static_cast<int>(ESTAT::DAMAGE)] << endl;
            break;
        case 4:
            status[static_cast<int>(ESTAT::ARMOR)] = status[static_cast<int>(ESTAT::ARMOR)] << 1;
            cout << " * 방어력이 2배로 증가되었습니다.\
                \n현재 방어력: " << status[static_cast<int>(ESTAT::ARMOR)] << endl;
            break;
        case 5:
            cout << " * Level : " << level << ", CLASS : " << eclass_to_string[static_cast<int>(char_class)] << ", HP : " << status[static_cast<int>(ESTAT::HP)] << ", MP : " << status[static_cast<int>(ESTAT::MP)]
                << ", 공격력 : " << status[static_cast<int>(ESTAT::DAMAGE)] << ", 방어력 : " << status[static_cast<int>(ESTAT::ARMOR)]
                << ", 힘 : " << status[static_cast<int>(ESTAT::STR)] << ", 민첩 : " << status[static_cast<int>(ESTAT::DEX)] << ", 지능 : " << status[static_cast<int>(ESTAT::INT)]
                << "\n남은 HP / MP 포션 수 : " << nr_HPPotion << " / " << nr_MPPotion << endl;
            break;
        case 6:
            levelUp(&level, status, char_class, &nr_HPPotion, &nr_MPPotion);
            cout << "* 레벨업! HP/MP 포션이 지급됩니다.\
                    \nLevel : " << level << ", 남은 HP / MP 포션 수 : " << nr_HPPotion << " / " << nr_MPPotion << endl;
            break;
        case 0:
            break;
        default:
            cout << "다시 입력하세요" << endl;
            break;
        }
    }
    cout << "프로그램을 종료합니다." << endl;


    return 0;
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = 5;
    *p_MPPotion = 5;
}

void levelUp(int* p_level, int* status, ECLASS char_class, int* p_HPPotion, int* p_MPPotion) {
    ++*p_level;
    ++*p_HPPotion;
    ++*p_MPPotion;
    ++status[primary_stat_idx[static_cast<int>(char_class)]];


}
