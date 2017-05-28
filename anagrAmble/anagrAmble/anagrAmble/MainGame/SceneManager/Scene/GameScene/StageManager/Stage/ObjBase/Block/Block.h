//==================================================================================================================================//
//!< @file		Block.h
//!< @brief		ar::Blockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BLOCK_H
#define AR_BLOCK_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面のブロックの基底クラス
//======================================================================//
class Block : public ObjBase
{

public:
	/** Constructor */
	Block(const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Block();

	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
	/** 
	* 処理実行関数
	* ObjBase::Constrol()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数
	* ObjBase::Draw()内で使用する
	*/
	virtual void Render(void)override;

	/** イベント処理関数 */
	virtual void HandleEvent(void)override;

};	// class Block

}	// namespace ar

#endif	// AR_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
