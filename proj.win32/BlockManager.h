#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "cocos2d.h"
#include "Block.h"
#include "DisplayManager.h"

using namespace cocos2d;

class BlockManager:public CCNode
{
public: 
	typedef enum
	{
		Empty,
		Dropping,
		Dead
	}CellState;
	static const int CellMatrixWidth = 10;
	static const int CellMatrixHeight = 20;
	static const int DefaultRefreshTime = 80;
	static const int RequiredUpdateTime = 2;

protected:
	int m_periodDropping;
	bool m_isKeyboardPressed;

	Block* m_blockDropping;
	Block* m_blockWaiting;

	CellState m_matrixCellState[BlockManager::CellMatrixWidth][BlockManager::CellMatrixHeight];
	CCSprite* m_matrixDeadBlockSprites[BlockManager::CellMatrixWidth][BlockManager::CellMatrixHeight];

	DisplayManger* m_boundDisplayManager;
	CCSpriteBatchNode* m_spriteBatchNodeDeadBlocks;


public: //系统调用
	
	BlockManager();
	~BlockManager();
	
	static BlockManager* create(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerTobind);
	virtual bool init(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerTobind);

	virtual void update(float p_delta); //定时刷新函数

	virtual void triggerKeyboard(int p_valueKey);

public: //公有自定义函数
	int getUpdateTime(); //获取更新时间
	void setUpdateTime(int p_updateTime);
	virtual CCPoint convertBlockPositionToPixelPosition(CCPoint p_pointBlock); //把网格坐标转化为实际坐标（右下角）
	virtual inline CCPoint convertPositionToCenterPosition(CCPoint p_pointRightBottom)
	{
		CCPoint pointResult = ccp(p_pointRightBottom.x + Block::CellSize / 2, p_pointRightBottom.y + Block::CellSize / 2);
		return pointResult;
	}
	void setKeyboardState(bool p_isKeyPressed); //设定按键按下状态 

protected: //私有自定义函数
	virtual Block* _createNewBlock(); //生成新的方块
	virtual void _pushNewBlock(); //生成新的nextBlock 修改Stage矩阵 并把原nextBlock推上舞台

	virtual bool _shouldBlockTryDrop(int updateTime); //判断当前方块是否应该下落一次
	virtual void _donotTryDrop(); //不尝试下落
	virtual void _doTryUpdateDrop(); //尝试定时下落
	virtual void _doTryMove(Block::Direction direction); //尝试平移
	virtual void _doTryRequiredDrop(); //尝试触发下落
	virtual void _doTryTurn90Degrees(); //尝试旋转90度

	virtual bool _currentBlockCanMove(Block::Direction direction); //判断方块是否可以向特定方向移动
	virtual void _currentBlockDoMove(Block::Direction direction); //使当前方块移动
	virtual void _currentBlockStopDrop(); //停止当前方块下落
	virtual bool _currentBlockCanTurn90Degrees(); //判断方块是否可以旋转90度
	virtual void _currentBlockDoTurn90Degrees(); //使当前方块旋转

	virtual void _updateCellMatrixBeforeMove(Block::Direction direction); //为Block移动更新单元矩阵
	virtual void _updateCellMatrixBeforeDie(); //为Block死亡更新单元矩阵
	virtual void _updateCellMatrixAfterChanged(Block::CellPosition originalPosition, Block::CellPosition newPosition); //用position更新矩阵
	virtual int _eliminateLines(); //尝试消除
	bool BlockManager::_blockOverlayed(Block::CellPosition p_block1, Block::CellPosition p_block2);
	virtual void _endGame(); //结束游戏

	virtual void _eliminateSingleLine(int lineNum); //消除单行（动画效果,清除数据等）
	virtual inline bool _isLineFilled(int lineNum)
	{
		for (int i = 0; i < BlockManager::CellMatrixWidth; i++)
		{
			if (this->m_matrixCellState[i][lineNum] != BlockManager::CellState::Dead)
			{
				return false;
			}
		}
		return true;
	} //判断该行是否已满
	virtual void _isTetris(int startLine); //Tetris动画
	virtual void _rePaintDeadBlocks(); //重绘dead blocks
	

}; //class BlockManager

#endif //!__BLOCK_MANAGER_H__