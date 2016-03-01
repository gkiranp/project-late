#ifndef WS_STORAGE_H
#define WS_STORAGE_H

#include <QString>
#include <QList>


#define WS_OP_TYPE_COUNT    2

typedef enum en_ws_operation_type {
    e_Op_DELETE = 1,
    e_Op_HIGHLIGHT = 2
}WS_OperationType;

#define WS_OP_SUBJ_COUNT    6

typedef enum en_ws_operation_subject {
    e_sub_ROW = 1,
    e_sub_COLUMN = 2,
    e_sub_DATE = 3,
    e_sub_TIME = 4,
    e_sub_STRING = 5,
    e_sub_CUSTOM = 6
}WS_OperationSubject;

typedef struct st_string_operation_type {
    WS_OperationType m_Type;
    QString          m_String;
}StringOperationType;

typedef struct st_string_operation_subject {
    WS_OperationSubject  m_SubType;
    QString              m_String;
    QString              m_Format;
    QString              m_Value;
}StringOperationSubject;

typedef struct st_ws_operation_storage
{
    WS_OperationType     m_OpType;
    WS_OperationSubject  m_OpSub;
    QString              m_OpFormat;
}WS_OperationStorage;

/***************************************************
 *
 * Workspace Storage Class
 *
 ***************************************************/

class ws_storage
{
public:
    ws_storage() {
        init_StrOpTypeList();
        init_StrOpSubjList();
        m_InitStatus = true;
    }

public:
    QList<StringOperationType>      m_StrOpType_Ref;
    QList<StringOperationSubject>   m_StrOpSub_Ref;
    bool                            m_InitStatus;

public:
    QString GetStr_OperationType(WS_OperationType type) {
        if(m_InitStatus) {
            StringOperationType a;
            for (int i = 0 ; i < m_StrOpType_Ref.count() ; i++) {
                a = m_StrOpType_Ref.at(i);
                if(a.m_Type == type) {
                    return a.m_String;
                }
            }
        }
    }

    WS_OperationType GetOpType_ByString(QString str)
    {
        if(m_InitStatus) {
            if(!str.isEmpty()) {
                for(int i = 0 ; i < m_StrOpType_Ref.count() ; i++) {
                    if(m_StrOpType_Ref.at(i).m_String == str) {
                        return m_StrOpType_Ref.at(i).m_Type;
                    }
                }
            }
        }
    }

    QString GetStr_OperationSubject(WS_OperationSubject sub) {
        if(m_InitStatus) {
            StringOperationSubject b;
            for (int i = 0 ; i < m_StrOpSub_Ref.count() ; i++) {
                b = m_StrOpSub_Ref.at(i);
                if(b.m_SubType == sub) {
                    return b.m_String;
                }
            }
        }
    }

    WS_OperationSubject GetOpSub_ByString(QString str)
    {
        if(m_InitStatus) {
            if(!str.isEmpty()) {
                for(int i = 0 ; i < m_StrOpSub_Ref.count() ; i++) {
                    if(m_StrOpSub_Ref.at(i).m_String == str) {
                        return m_StrOpSub_Ref.at(i).m_SubType;
                    }
                }
            }
        }
    }

    QString GetStr_OperationFormat(WS_OperationSubject sub) {
        if(m_InitStatus) {
            StringOperationSubject c;
            for (int i = 0 ; i < m_StrOpSub_Ref.count() ; i++) {
                c = m_StrOpSub_Ref.at(i);
                if(c.m_SubType == sub) {
                    return c.m_Format;
                }
            }
        }
    }

private:
    void init_StrOpTypeList(void) {
        StringOperationType entry;
        // add 1
        entry.m_Type = e_Op_DELETE;
        entry.m_String = "DELETE";
        m_StrOpType_Ref.append(entry);
        // add 2
        entry.m_Type = e_Op_HIGHLIGHT;
        entry.m_String = "HIGHLIGHT";
        m_StrOpType_Ref.append(entry);
    }

    void init_StrOpSubjList(void) {
        StringOperationSubject entry;
        //add 1
        entry.m_SubType = e_sub_ROW;
        entry.m_String  = "ROW";
        entry.m_Format  = "Enter row number (not a Reg-Exp)";
        entry.m_Value   = "0";
        m_StrOpSub_Ref.append(entry);
        //add 2
        entry.m_SubType = e_sub_COLUMN;
        entry.m_String  = "COLUMN";
        entry.m_Format  = "Enter column number (not a Reg-Exp)";
        entry.m_Value   = "0";
        m_StrOpSub_Ref.append(entry);
        //add 3
        entry.m_SubType = e_sub_DATE;
        entry.m_String  = "DATE";
        entry.m_Format  = "Edit date format (Reg-Exp)";
        entry.m_Value   = "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) (\\\\d\\\\d)";
        m_StrOpSub_Ref.append(entry);
        //add 4
        entry.m_SubType = e_sub_TIME;
        entry.m_String  = "TIME";
        entry.m_Format  = "Edit time format (Reg-Exp)";
        entry.m_Value   = "(\\\\d\\\\d:\\\\d\\\\d:\\\\d\\\\d)";
        m_StrOpSub_Ref.append(entry);
        //add 5
        entry.m_SubType = e_sub_STRING;
        entry.m_String  = "STRING";
        entry.m_Format  = "Enter a string (Reg-Exp)";
        entry.m_Value   = "(\\\\w+)";
        m_StrOpSub_Ref.append(entry);
        //add 6
        entry.m_SubType = e_sub_CUSTOM;
        entry.m_String  = "CUSTOM REG EXP";
        entry.m_Format  = "Enter your custom Reg-Exp format";
        entry.m_Value   = "(*)";
        m_StrOpSub_Ref.append(entry);
    }
};

#endif // WS_STORAGE_H
