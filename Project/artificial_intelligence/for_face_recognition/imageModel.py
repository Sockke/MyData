'''
    数据层
'''
import sql


class ImageModel(object):
    def __init__(self):
        pass

    def add_image(self, face_encoding, name):
        '''添加图片资源'''
        conn = sql.Sqlite()
        conn.connect()
        # sql_str = f"insert into {conn.table}(encoding,name) values('{face_encoding}', '{name}');"
        sql_str = "insert into %s(encoding, name) values('%s', '%s');"%(conn.table, face_encoding, name)
        conn.modify(sql_str)
        
    def fetch_image(self):
        '''获取图片资源'''
        conn = sql.Sqlite()
        conn.connect()
        sql_str = f"select * from {conn.table};"
        data = conn.query(sql_str)
        return data

