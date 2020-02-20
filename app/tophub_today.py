

import requests

from pyquery import PyQuery as pq
import pymysql
import datetime
import numpy as np


def get_txt():
    headers = {
        "accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
        "accept-encoding": "gzip, deflate, br",
        "accept-language": "zh-CN,zh;q=0.9,en;q=0.8",
        "cache-control": "max-age=0",
        "cookie": "Hm_lvt_3b1e939f6e789219d8629de8a519eab9=1581650041,1581672289,1582133570,1582185779; Hm_lpvt_3b1e939f6e789219d8629de8a519eab9=1582186093",
        "sec-fetch-dest": "document",
        "sec-fetch-mode": "navigate",
        "sec-fetch-site": "none",
        "sec-fetch-user": "?1",
        "upgrade-insecure-requests": "1",
        "user-agent": "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/82.0.4056.3 Safari/537.36",

    }
    url = "https://tophub.today"

    rep = requests.get(url, headers = headers)

    return rep.text



def get_info(doc, up_date ,max_item=10):
    data = []
    tcs = doc(".bc-tc")
    for tc in tcs.items():
        info_class = tc.text()
        cds = tc.next(".bc-cc .cc-cd")
        for cd in cds.items():
            plat = cd(".cc-cd-lb span").text()
            hot_class = cd(".cc-cd-sb span").text()
            cb_l_a = cd(".cc-cd-cb-l a")
            for a in list(cb_l_a.items())[:max_item]:
                url = a('a').attr("href")
                cb_ll = a('.cc-cd-cb-ll')

                rank = int(cb_ll(".s").text())
                title = cb_ll(".t").text()
                hot = cb_ll(".e").text()
                if hot == "":
                    hot = None
                data.append((info_class, plat, rank, title, hot, hot_class, up_date, url))
    col_l = ["info_class", "plat", "rank", "title", "hot", "hot_class", "up_date", "url"]
    return col_l, data

def store_data(col_l, data):
    
    col = ",".join(col_l)
    val = ",".join(np.repeat("%s",len(col_l)))
    sql = "insert into info(%s) values(%s)" %(col, val)
    MYSQL_MALL_DIC = {
        "user":"root",
        "password":"jiuguai",
        "host":"localhost",
        "port":3306,
        "database":"today",
        "charset" :"utf8mb4"
    }
    try:
        conn = pymysql.connect(**MYSQL_MALL_DIC)
        cursor =  conn.cursor()
        # 当天只 保留一份  其他都删除
        cursor.execute("select max(up_date) from info")
        result = cursor.fetchone()
        cursor.execute("delete from info where up_date=%s",result)
        conn.commit()

        cursor.executemany(sql, data)
        conn.commit()
        conn.close()
    except:
        conn.close()


    
def run():
    today = datetime.datetime.today().date()
    print('获取网页信息')
    txt = get_txt()
    doc = pq(txt)
    print('提取数据')
    col_l, data = get_info(doc, today, 10)
    print('存入数据库')
    store_data(col_l, data)
    print('执行完成')

if __name__ == "__main__":
    run()