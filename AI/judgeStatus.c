#include "base.h"

/**
 * @brief 判断连子类型
 * @param length 长度
 * @param first_status 开始是否阻塞
 * @param end_status 结束是否阻塞
 * @return 连子类型
*/
Grade judgeStatus(int length, bool first_status, bool end_status)
{
    if (true == first_status)
    {
        if (true == end_status)
        {
            switch (length)
            {
            case 5: return CON_FIVE;
            case 4: return ACTIVE_FOUR;
            case 3: return ACTIVE_THREE;
            case 2: return ACTIVE_TWO;
            case 1: return ACTIVE_ONE;
            default:
                break;
            }
        }
        else
        {
            switch (length)
            {
            case 4: return INACTIVE_FOUR;
            case 3: return INACTIVE_THREE;
            case 2: return INACTIVE_TWO;
            default: break;
            }
        }
    }
    else
    {
        if (true == end_status)
        {
            switch (length)
            {
            case 4: return INACTIVE_FOUR;
            case 3: return INACTIVE_THREE;
            case 2: return INACTIVE_TWO;
            default: break;
            }
        }
        else
        {}
    }

    return -1;
}