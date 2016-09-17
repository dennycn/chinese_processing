//compile：
// gcc -o test testscws.c -lscws -L../../.commonlib/lib 
// -I../../commonlib/include
//refer: http://www.ftphp.com/scws/docs.php
#include <stdlib.h>
#include <math.h>
#include "../scws.h"

int main()
{
  scws_t s;
  scws_res_t res, cur;
  char *text = "Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言";

  if (!(s = scws_new())) {
    printf("error, can't init the scws_t!\n");
    exit(-1);
  }
  scws_set_charset(s, "gbk");
  scws_set_dict(s, "/usr/local/scws/etc/dict.xdb", SCWS_XDICT_XDB);
  scws_set_rule(s, "/usr/local/scws/etc/rules.ini");

  scws_send_text(s, text, strlen(text));
  while (res = cur = scws_get_result(s))
  {
    while (cur != NULL)
    {
      printf("Word: %.*s/%s (IDF = %4.2f)\n",
        cur->len, text+cur->off, cur->attr, cur->idf);
      cur = cur->next;
    }
    scws_free_result(res);
  }
  scws_free(s);

  return 0;
}

//#include "classifier/CScws.h"
//int main(){
//        char *text = "Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言";
//        char _m_buf[512];
//        int buf_len = 0;
//        int cutLen = CScws::instance().cutword(text, strlen(text), _m_buf, buf_len);
//        printf("cutlen=%d, %s\n", cutLen, _m_buf);
//        return 0;
//}
