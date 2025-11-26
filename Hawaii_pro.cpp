/*
Consonant(s) Pronunciation Rule
p, k, h, l, m, n Pronounced like the English versions.
w (start of word) Either pronounced as w or v. We shall pronounce it as w.
w (after a) Either pronounced as w or v. We shall pronounce it as w.
w (after i or e) Pronounced as a v sound.
w (after u or o) Pronounced as a w sound



Vowel Pronunciation Rule
a sounds like ah. eg. like that in "Austin" (ah-stin)
e sounds like eh. eg. like that in "egg" (eh-gg)
i sounds like ee. eg. like that in "bee"
o sounds like oh. eg. like that in "obey" (oh-bay)
u sounds like oo. eg. like that in "mood" (moo-d)


Vowel groups Pronunciation Rule
ai sounds like eye. eg. like that in "ice"
ae sounds like eye, same as ai
ao sounds like ow. eg. like that in "how"
au sounds like ow. eg. like that in "house"
ei sounds like ay. eg. like that in "hay"
eu sounds like eh-oo.
iu sounds like ew.
oi sounds like oy.
ou sounds like ow.
ui sounds like ooey. eg. like that in "gooey"


• Chương trình phải kiểm tra các từ chỉ chứa các ký tự hợp lệ trong tiếng Hawaii. Dấu cách và
dấu nháy đơn (') cũng được xem là hợp lệ.
• Nếu từ không hợp lệ, chương trình phải cảnh báo người dùng về các ký tự không hợp lệ.
• Dấu cách biểu thị sự ngắt quãng giữa các từ và phải được giữ nguyên.
• Dấu nháy đơn biểu thị sự ngắt quãng phát âm và phải được giữ nguyên trong từ. Ví dụ, từ a'i
được phát âm là ah'ee. Nếu không có dấu nháy đơn, từ đó sẽ được phát âm thành eye.
• Không được phép sử dụng phương thức .replace(). Sinh viên phải xử lý các ký tự được nhập
vào từng ký tự một theo đúng quy tắc.
• Ngoài mảng (array), không được phép sử dụng các cấu trúc dữ liệu khác.
• Hãy cẩn thận khi dùng int trong các vòng lặp liên quan đến string.size(). Hàm .size()
trả về một kiểu số không dấu (size_t), trong khi int là số có dấu.

Trong bài tập này, sinh viên sẽ viết một chương trình nhận vào một từ tiếng Hawaii và xuất ra
cách phát âm của từ đó theo đúng quy tắc ngữ âm. Ví dụ, từ humuhumunukunukuapua'a sẽ được phát
âm thành hoo-moo-hoo-moo-noo-koo-noo-koo-ah-poo-ah'ah.

*/

#include <iostream>
#include <string>
#include <cctype>

std::string change(char c)
{
    if (c == 'a')
        return "ah";
    if (c == 'e')
        return "eh";
    if (c == 'i')
        return "ee";
    if (c == 'o')
        return "oh";
    if (c == 'u')
        return "oo";
    return std::string(1, c);
}

std::string changeCombo(std::string x)
{
    if (x == "ai" || x == "ae")
        return "eye";
    if (x == "ao" || x == "au")
        return "ow";
    if (x == "ei")
        return "ay";
    if (x == "eu")
        return "eh-oo";
    if (x == "iu")
        return "ew";
    if (x == "oi")
        return "oy";
    if (x == "ou")
        return "ow";
    if (x == "ui")
        return "ooey";
    return std::string(x);
}

bool isVol(char c)
{
    if (c == 'e' || c == 'u' || c == 'a' || c == 'i' || c == 'o')
    {
        return true;
    }
    return false;
}

bool isCon(char x)
{
    // pkhlmnw
    if (x == 'p' || x == 'k' || x == 'l' || x == 'm' || x == 'w' || x == 'h' || x == 'n')
    {
        return true;
    }
    return false;
}

void solve(std::string sum)
{
    std::string s = "";
    for (std::size_t i = 0; i < sum.size(); ++i)
    {
        char k = sum[i];
        s += std::tolower(k);
    }

    for (std::size_t i = 0; i < s.size(); ++i)
    {
        char x = s[i];

        if (!isVol(x) && !isCon(x) && x != ' ' && x != '\'')
        {
            std::cout << sum << " contains invalid characters." << std::endl;
            return;
        }
    }

    std::string result = "";

    for (std::size_t i = 0; i < s.size(); ++i)
    {
        // Xu ly dau cach
        if (s[i] == ' ')
        {
            result += s[i];
            continue;
        }

        // Xu ly dau nhay don - xoa dau gach truoc neu co
        if (s[i] == '\'')
        {
            if (result.length() > 0 && result[result.length() - 1] == '-')
            {
                result = result.substr(0, result.length() - 1);
            }
            result += '\'';
            continue;
        }

        // Xu ly phu am
        if (isCon(s[i]))
        {
            if (s[i] == 'w')
            {
                // Tim nguyen am gan w nhat - bo qua dau cach va dau nhay
                int j = i - 1;
                while (j >= 0 && (s[j] == ' ' || s[j] == '\''))
                {
                    j--;
                }

                if (j < 0)
                {
                    // W la tu bat dau cua ki tu
                    result += 'w';
                }
                else
                {
                    char prev = s[j];
                    if (prev == 'i' || prev == 'e') // neu truoc do la i va e
                    {
                        result += 'v';
                    }
                    else if (prev == 'a' || prev == 'u' || prev == 'o') // neu truoc do la a u o
                    {
                        result += 'w';
                    }
                    else
                    {
                        result += 'w';
                    }
                }
            }
            else // Khong phai w
            {
                result += s[i];
            }
            continue;
        }

        // Xu ly nguyen am - dau nhay - nguyen am
        if (i + 2 < s.length() && isVol(s[i]) && s[i + 1] == '\'' && isVol(s[i + 2]))
        {
            result += change(s[i]);
            result += "'";
            result += change(s[i + 2]);

            i += 2;

            if (i < s.length() - 1 && s[i + 1] != ' ' && s[i + 1] != '\'')
            {
                result += '-';
            }

            continue; // skip toi vong for tiep theo
        }

        // Xu ly cap nguyen am
        bool foundCombo = false;
        if (i < s.length() - 1 && isVol(s[i]) && isVol(s[i + 1]))
        {
            std::string temp = "";
            temp += s[i];
            temp += s[i + 1];
            std::string convert = changeCombo(temp);
            if (convert != temp)
            {
                result += convert;
                ++i;
                if (i < s.length() - 1 && s[i + 1] != ' ' && s[i + 1] != '\'')
                {
                    result += '-';
                }

                foundCombo = true;
            }
        }

        // Xu ly nguyen am don
        if (!foundCombo)
        {
            if (isVol(s[i]))
            {
                result += change(s[i]);
                if (i < s.length() - 1 && s[i + 1] != ' ' && s[i + 1] != '\'')
                {
                    result += '-';
                }
            }
        }
    }

    // Xoa dau gach cuoi cung neu co
    if (result.length() > 0 && result[result.length() - 1] == '-')
    {
        result = result.substr(0, result.length() - 1);
    }

    std::cout << result << std::endl;
}

int main()
{
    std::string word;

    std::getline(std::cin, word);

    solve(word);
}
