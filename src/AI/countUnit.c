#include "base.h"

/**
 * @brief 计算单元
 * @param array[] 一维数组
 * @param array_lenght 数组长度
 * @param self_type 己方种类
 * @param self 己方分数类型记分
 * @param enemy 敌方分数类型记分
*/
void countUnit(const int array[], const int array_lenght, const Type self_type, Count *self, Count *enemy)
{
    if (NULL == array)
    {
        return;
    }
    if (1 >= array_lenght)
    {
        return;
    }
    const Type ENEMY_COLOR = (BLACK == self_type) ? WHITE : BLACK; //敌人
    int length = 0;
    bool first_status = false;
    bool end_status = false;

    for (int i = 0; i <= array_lenght-3; i++)
    {
        const Type now_type = *(array+i);
        const Type next_type = *(array+i+1);

        //空判断
        if (EMPTY == now_type)
        {
            first_status = true;
            continue;
        }
        
        
        
        if (next_type == now_type)
        {
            length++;
        }
        else if (EMPTY == next_type)
        {
            length++;
            end_status = true;

            //更新连子状态
            if (self_type == now_type)
            {
                switch (judgeStatus(length, first_status, end_status))
                {
                    case CON_FIVE: self->con_five++; break;
                    case ACTIVE_FOUR: self->active_four++; break;
                    case ACTIVE_THREE: self->active_three++; break;
                    case ACTIVE_TWO: self->active_two++; break;
                    case ACTIVE_ONE: self->active_one++; break;
                    case INACTIVE_FOUR: self->inactive_four++; break;
                    case INACTIVE_THREE: self->inactive_three++; break;
                    case INACTIVE_TWO: self->inactive_two++; break;
                    default: break;
                }
            }
            else
            {
                switch (judgeStatus(length, first_status, end_status))
                {
                    case CON_FIVE: enemy->con_five++; break;
                    case ACTIVE_FOUR: enemy->active_four++; break;
                    case ACTIVE_THREE: enemy->active_three++; break;
                    case ACTIVE_TWO: enemy->active_two++; break;
                    case ACTIVE_ONE: enemy->active_one++; break;
                    case INACTIVE_FOUR: enemy->inactive_four++; break;
                    case INACTIVE_THREE: enemy->inactive_three++; break;
                    case INACTIVE_TWO: enemy->inactive_two++; break;
                    default: break;
                }
            }
            
            length = 0;
        }
        else
        {
            length++;
            end_status = false;

            //更新连子状态
            if (self_type == now_type)
            {
                switch (judgeStatus(length, first_status, end_status))
                {
                    case CON_FIVE: self->con_five++; break;
                    case ACTIVE_FOUR: self->active_four++; break;
                    case ACTIVE_THREE: self->active_three++; break;
                    case ACTIVE_TWO: self->active_two++; break;
                    case ACTIVE_ONE: self->active_one++; break;
                    case INACTIVE_FOUR: self->inactive_four++; break;
                    case INACTIVE_THREE: self->inactive_three++; break;
                    case INACTIVE_TWO: self->inactive_two++; break;
                    default: break;
                }
            }
            else
            {
                switch (judgeStatus(length, first_status, end_status))
                {
                    case CON_FIVE: enemy->con_five++; break;
                    case ACTIVE_FOUR: enemy->active_four++; break;
                    case ACTIVE_THREE: enemy->active_three++; break;
                    case ACTIVE_TWO: enemy->active_two++; break;
                    case ACTIVE_ONE: enemy->active_one++; break;
                    case INACTIVE_FOUR: enemy->inactive_four++; break;
                    case INACTIVE_THREE: enemy->inactive_three++; break;
                    case INACTIVE_TWO: enemy->inactive_two++; break;
                    default: break;
                }
            }
            length = 0;
            first_status = false;
        }
    }
    
    //尾判断
    {
        const Type now_type = *(array+array_lenght-2);
        const Type next_type = *(array+array_lenght-1);

        //空判断
        if (EMPTY == now_type)
        {
            first_status = true;
            if (EMPTY != next_type)
            {
                //更新连子状态
                if (self_type == now_type)
                {
                    switch (judgeStatus(1, first_status, end_status))
                    {
                        case CON_FIVE: self->con_five++; break;
                        case ACTIVE_FOUR: self->active_four++; break;
                        case ACTIVE_THREE: self->active_three++; break;
                        case ACTIVE_TWO: self->active_two++; break;
                        case ACTIVE_ONE: self->active_one++; break;
                        case INACTIVE_FOUR: self->inactive_four++; break;
                        case INACTIVE_THREE: self->inactive_three++; break;
                        case INACTIVE_TWO: self->inactive_two++; break;
                        default: break;
                    }
                }
                else
                {
                    switch (judgeStatus(1, first_status, end_status))
                    {
                        case CON_FIVE: enemy->con_five++; break;
                        case ACTIVE_FOUR: enemy->active_four++; break;
                        case ACTIVE_THREE: enemy->active_three++; break;
                        case ACTIVE_TWO: enemy->active_two++; break;
                        case ACTIVE_ONE: enemy->active_one++; break;
                        case INACTIVE_FOUR: enemy->inactive_four++; break;
                        case INACTIVE_THREE: enemy->inactive_three++; break;
                        case INACTIVE_TWO: enemy->inactive_two++; break;
                        default: break;
                    }
                }
            
            }
        }
        else
        {
            if (EMPTY == next_type)
            {
                length++;
                end_status = true;
                //更新连子状态
                if (self_type == now_type)
                {
                    switch (judgeStatus(length, first_status, end_status))
                    {
                        case CON_FIVE: self->con_five++; break;
                        case ACTIVE_FOUR: self->active_four++; break;
                        case ACTIVE_THREE: self->active_three++; break;
                        case ACTIVE_TWO: self->active_two++; break;
                        case ACTIVE_ONE: self->active_one++; break;
                        case INACTIVE_FOUR: self->inactive_four++; break;
                        case INACTIVE_THREE: self->inactive_three++; break;
                        case INACTIVE_TWO: self->inactive_two++; break;
                        default: break;
                    }
                }
                else
                {
                    switch (judgeStatus(length, first_status, end_status))
                    {
                        case CON_FIVE: enemy->con_five++; break;
                        case ACTIVE_FOUR: enemy->active_four++; break;
                        case ACTIVE_THREE: enemy->active_three++; break;
                        case ACTIVE_TWO: enemy->active_two++; break;
                        case ACTIVE_ONE: enemy->active_one++; break;
                        case INACTIVE_FOUR: enemy->inactive_four++; break;
                        case INACTIVE_THREE: enemy->inactive_three++; break;
                        case INACTIVE_TWO: enemy->inactive_two++; break;
                        default: break;
                    }
                }
                length = 0;
            }
            else
            {
                if (next_type == now_type)
                {
                    end_status = false;
                    length += 2;
                    //更新连子状态
                    if (self_type == now_type)
                    {
                        switch (judgeStatus(length, first_status, end_status))
                        {
                            case CON_FIVE: self->con_five++; break;
                            case ACTIVE_FOUR: self->active_four++; break;
                            case ACTIVE_THREE: self->active_three++; break;
                            case ACTIVE_TWO: self->active_two++; break;
                            case ACTIVE_ONE: self->active_one++; break;
                            case INACTIVE_FOUR: self->inactive_four++; break;
                            case INACTIVE_THREE: self->inactive_three++; break;
                            case INACTIVE_TWO: self->inactive_two++; break;
                            default: break;
                        }
                    }
                    else
                    {
                        switch (judgeStatus(length, first_status, end_status))
                        {
                            case CON_FIVE: enemy->con_five++; break;
                            case ACTIVE_FOUR: enemy->active_four++; break;
                            case ACTIVE_THREE: enemy->active_three++; break;
                            case ACTIVE_TWO: enemy->active_two++; break;
                            case ACTIVE_ONE: enemy->active_one++; break;
                            case INACTIVE_FOUR: enemy->inactive_four++; break;
                            case INACTIVE_THREE: enemy->inactive_three++; break;
                            case INACTIVE_TWO: enemy->inactive_two++; break;
                            default: break;
                        }
                    }
                
                }
                else
                {
                    end_status = false;
                    length++;
                    //更新连子状态
                    if (self_type == now_type)
                    {
                        switch (judgeStatus(length, first_status, end_status))
                        {
                            case CON_FIVE: self->con_five++; break;
                            case ACTIVE_FOUR: self->active_four++; break;
                            case ACTIVE_THREE: self->active_three++; break;
                            case ACTIVE_TWO: self->active_two++; break;
                            case ACTIVE_ONE: self->active_one++; break;
                            case INACTIVE_FOUR: self->inactive_four++; break;
                            case INACTIVE_THREE: self->inactive_three++; break;
                            case INACTIVE_TWO: self->inactive_two++; break;
                            default: break;
                        }
                    }
                    else
                    {
                        switch (judgeStatus(length, first_status, end_status))
                        {
                            case CON_FIVE: enemy->con_five++; break;
                            case ACTIVE_FOUR: enemy->active_four++; break;
                            case ACTIVE_THREE: enemy->active_three++; break;
                            case ACTIVE_TWO: enemy->active_two++; break;
                            case ACTIVE_ONE: enemy->active_one++; break;
                            case INACTIVE_FOUR: enemy->inactive_four++; break;
                            case INACTIVE_THREE: enemy->inactive_three++; break;
                            case INACTIVE_TWO: enemy->inactive_two++; break;
                            default: break;
                        }
                    }
                    length = 0;
                }
            }
        }
    }
}