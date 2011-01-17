/**
 * @file      PinyinConv.cpp
 * @brief      
 * @author  wuqifu denny@pku.edu.cn
 * @date    2010-6-17
 */

#include "PinyinConv.h"
#include <string.h>

namespace Pinyin
{

// one level pinyin dict: 26 alphabet
//static char GBPinYinList[53]={'∞°∞≈≤¡¥Ó∂Í∑¢∏¡π˛ª˜ª˜ø¶¿¨¬Ëƒ√≈∂≈æ∆⁄»ª»ˆÀ˙Õ⁄Õ⁄Õ⁄ŒÙ—π‘—'};

// add worddict for stock :   20 words per line, now is 39, endwith "", add by Denny, 2010-7-21            
string PinyinConv::stockGBList[]={"ÔΩ", "ÔØ", "›∏", "‹Ω", "Ê⁄", "Íª", "Â∑", "Ò•", "ÍÕ", "Ë¢", "ÿ", "„Ú", "Èµ", "ÚÎ", "ÔÆ", "‰", "·∫", "Ó‚", "Âß", "Á˘", 
                        "Á˜", "‹ı", "È≈","Í…", "Ó—", "Û´", "Ó„", "„˚", "––", "ˆŒ", "‰±", "Ï˚", "·≠", "Ÿ", "Ó⁄", "‚˘","Æ", "€⁄", "‚Ø", "Ëœ", ""};
string PinyinConv::stockGBpyList[]={"de","gao", "guan", "fu", "fu","hao", "huan", "huang", "hui", "ju", "lu", "lu", "lu", "lang", "li", "luo", "min", "mu", "pu", "qi",
                        "qi", "quan", "rong", "sheng", "tai", "tang", "tan", "tuo","hang", "xin","xun", "xi", "xian","yan", "yu", "yi", "yong", "zhen", "zhang","zhe", ""};

// convert chinese word to pinyin  {pyvalue, pystr}={-20319, 'a'}
int PinyinConv::pyvalue[PINYINNUM] =  {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
   -20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,-19725,-19715,
   -19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,-19261,-19249,-19243,-19242,
   -19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,-18977,-18961,-18952,-18783,-18774,-18773,
   -18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,-18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,
   -18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,-18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,
   -17928,-17922,-17759,-17752,-17733,-17730,-17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,
   -17433,-17427,-17417,-17202,-17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,
   -16465,-16459,-16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
   -16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,-15707,-15701,
   -15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,-15408,-15394,-15385,-15377,
   -15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,-15143,-15141,-15140,-15139,-15128,-15121,
   -15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,-14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,
   -14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,-14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,
   -14368,-14355,-14353,-14345,-14170,-14159,-14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,
   -14097,-14094,-14092,-14090,-14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,
   -13831,-13658,-13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
   -13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,-12860,-12858,
   -12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,-12320,-12300,-12120,-12099,
   -12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,-11589,-11536,-11358,-11340,-11339,-11324,
   -11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,-11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,
   -10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,-10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,
   -10262,-10260,-10256,-10254};

string PinyinConv::pystr[PINYINNUM] =  {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao","bie","bin","bing","bo",
        "bu", "ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen","cheng","chi","chong","chou","chu","chuai","chuan",
        "chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui","cun","cuo",
        "da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan","dui","dun","duo",
        "e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao","ge","gei","gen","geng","gong","gou","gu","gua","guai",
        "guan","guang","gui","gun","guo","ha","hai","han","hang","hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo",
        "ji","jia","jian","jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken","keng","kong","kou","ku","kua",
        "kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei","leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv",
        "luan","lue","lun","luo","ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
        "na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong","nu","nv","nuan","nue","nuo","o","ou",
        "pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie","pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong",
        "qiu","qu","quan","que","qun","ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang","sao","se","sen",
        "seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua","shuai","shuan","shuang","shui","shun","shuo","si","song",
        "sou","su","suan","sui","sun","suo","ta","tai","tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo","wa",
        "wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing","xiong","xiu","xu","xuan","xue","xun","ya","yan","yang",
        "yao","ye","yi","yin","ying","yo","yong","you","yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
        "zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo","zi","zong","zou","zu","zuan","zui","zun",
        "zuo"};


PinyinConv *PinyinConv::_instance = NULL;

PinyinConv::PinyinConv()
{
        _m_pyMap.clear();
        //stockGBList[i] endwith ""
        for(int i = 0;  stockGBList[i].size() ; i++)
        {      printf("i=%d\n", i);
                _m_pyMap.insert(make_pair( getGBValue(stockGBList[i].c_str(), 1), stockGBpyList[i]));
        }
}

/**
 * @brief 
 * @return
 */
PinyinConv *PinyinConv::get_instance ( void )
{
    if ( PinyinConv::_instance == NULL ) {
        PinyinConv::_instance = new PinyinConv;
    }
    return PinyinConv::_instance;
}

/*
 * @brief chinese charset convet to the pinyin frist spell
 * @input const char*
 * @return string
 */
string PinyinConv::getFirstSpell(const char* src)
{
        if( !src )
                return NULL;
        string result;
        int iAscii;
        char *p = (char*)src;
        while (*p) {
                if (*p > 0) {    //ascii:  a-z, A-Z, 0-9 ....
                        if ( *p >= 'a' &&  *p <= 'z')
                                result += (char)( *p - 'a' + 'A');
                        else
                                result += *p;
                        p++;
                } else {        // chinese word
                        string ret;
			// gbk code scope: {0xB0A1--0XD7FA}, 
                        // i, u, v isn't initial consonant of chinese syllable
                        iAscii = getGBValue(p);
                        if ( iAscii < 0xB0A1 || iAscii >= 0xF7FE) { p+=1; continue; }
                        result+=(char)getGBJP(iAscii);
                        p+=2;
                }
        } //end while(*p)
        return result;
}

/*
 * @input const char*
 * @return string
 */
string PinyinConv::getFullSpell(const char* src)
{
        if( !src )
                return NULL;
	string result;
        int iAscii, i=0;
        int len = strlen(src);
        char *p = (char*)src;
        while ( i < len) {
                iAscii = getGBValue(p, 2);
                if (iAscii > 0 && iAscii < 160) { //signeal char
                    result += *(p+i);
                    i++;
                    continue;
                }
                else if (iAscii < -20319 || iAscii > -10247) { //unkonew char
                    i++;
                    continue;
                }
                else {        // chinese word
                        string ret;
                        for (int j = PINYINNUM; j >= 0; j--) {
                               if (pyvalue[j] <= iAscii) {
                                       result += pystr[j];
                                       break;
                               }
                        }  //end for
                       p+=2;
                } // end else
        } //end while(*p)
	return result;
}

// return: 1-ture, 0-false
bool PinyinConv::isGBCode(const char* src)
{
        if ((unsigned char)*src>=0xb0 && (unsigned char)*src<=0xf7 && (unsigned char)src[1]>=0xa1 && (unsigned char)src[1]<=0xfe)
                return 1;
        return 0;
}

// return: 
int PinyinConv::getGBValue(const char* src, int type)
{
        // return unsigned  int
        if( 1 == type )
        {
                return (unsigned char)src[0]*256+(unsigned char)src[1];
        }
        else
        {      // return signed int
            int hightByte = 256 + src[0];
            int lowByte = 256 + src[1];

            int iascii = (256 * hightByte + lowByte) - 256 * 256;
            return iascii;
        }
        return 0;
}

char PinyinConv::getGBJP(int iAscii)
{
        // first find from speical word dict
        map<int, string>::iterator ite=_m_pyMap.find(iAscii);
        if ( ite != _m_pyMap.end())
        {
                return  ite->second.c_str()[0];
        }
        char ret = '?';
        if ( iAscii < 0xB0C5) ret = 'a';
        else if ( iAscii < 0xB2C1) ret = 'b';
        else if ( iAscii < 0xB4EE) ret = 'c';
        else if ( iAscii < 0xB6EA) ret = 'd';
        else if ( iAscii < 0xB7A2) ret = 'e';
        else if ( iAscii < 0xB8C1) ret = 'f';
        else if ( iAscii < 0xB9FE) ret = 'g';
        else if ( iAscii < 0xBBF7) ret = 'h';
        else if ( iAscii < 0xBFA6) ret = 'j';
        else if ( iAscii < 0xC0AC) ret = 'k';
        else if ( iAscii < 0xC2E8) ret = 'l';
        else if ( iAscii < 0xC4C3) ret = 'm';
        else if ( iAscii < 0xC5B6) ret = 'n';
        else if ( iAscii < 0xC5BE) ret = 'o';
        else if ( iAscii < 0xC6DA) ret = 'p';
        else if ( iAscii < 0xC8BB) ret = 'q';
        else if ( iAscii < 0xC8F6) ret = 'r';
        else if ( iAscii < 0xCBFA) ret = 's';
        else if ( iAscii < 0xCDDA) ret = 't';
        else if ( iAscii < 0xCEF4) ret = 'w';
        else if ( iAscii < 0xD1B9) ret = 'x';
        else if ( iAscii < 0xD4D1) ret = 'y';
        else if ( iAscii < 0xD7FA) ret = 'z';
         // Note: The next charsets have no laws,  need to more big wordDict.
        else ret = '?';    
        return ret;
}

extern "C" {
    string getFirstSpell(const char* src)
    {      
        return PinyinConv::get_instance()->getFirstSpell(src);
    }

    string getFullSpell(const char* src)
    {      
        return PinyinConv::get_instance()->getFullSpell(src);
    }

}  // end extern "C"

//int main()
//{
//	const char* src ="÷–π˙»À√Ò“¯––";
//	printf("{%s} convert first spell is {%s}\n", src, Pinyin::getFirstSpell(src).c_str());
//	printf("{%s} convert full spell is {%s}\n", src, Pinyin::getFullSpell(src).c_str());
//        return 0;
//}


} // end namespace

