//==================================================================================================================================//
//!< @file		slDX11Library.h
//!< @brief		sl::DX11Libraryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DX11_LIBRARY_H
#define SL_DX11_LIBRARY_H

#include "../slISharokuLibrary.h"
#include "../Common/slInputEnum.h"

namespace sl
{

class CustomizeInputManager;

namespace dx11
{
	
class Window;
class GraphicsDevice;
class TextureManager;
class Vertex2DManager;

}	// namespace dx11

namespace di
{

class InputManager;

}	// namespace di

namespace xi
{

class GamePad;

}	// namespace di

//======================================================================//
//!< DirectX11のライブラリのFacadeクラス
//======================================================================//
class DX11Library : public ISharokuLibrary
{

public:

	/** Constructor */
	DX11Library(void);

	/** Destructor */
	virtual ~DX11Library(void);

	SL_DISALLOW_COPY_AND_ASSIGN(DX11Library);

	//-----------------------------------------------------------------//
	// 初期化&破棄関連関数
	//-----------------------------------------------------------------//

	/** 
	* 初期化関数 
	* @param[in] pWinTitle		ウィンドウのタイトル
	* @param[in] winWidth		ウィンドウの横幅
	* @param[in] winHeight		ウィンドウの縦幅
	*/
	virtual void Initialize(t_char*  pWinTitle, int winWidth, int winHeight)override;

	/** 破棄関数 */
	virtual void Finalize(void)override;

	//-----------------------------------------------------------------//
	// Window関連関数
	//-----------------------------------------------------------------//

	/** 
	* ウィンドウ更新関数
	* @return ウィンドウが破棄されたかどうか true = 破棄された false = 破棄されていない
	*/
	virtual bool UpdateWindow(void)override;

	/** 
	* スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウモード
	*/
	virtual void ChangeWindowMode(bool isFullScreen)override;

	//-----------------------------------------------------------------//
	// テクスチャー関連関数
	//-----------------------------------------------------------------//

	/** 
	* 指定したパスのテクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイルネーム
	* @return 登録したID
	*/
	virtual int LoadTexture(const t_char* pFileName)override;

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] texID 解放したいテクスチャーのID
	*/
	virtual void ReleaseTex(int texID)override;

	/**現在読み込んでいるテクスチャー全てを解放する関数 */
	virtual void ReleaseTexALL(void)override;

	//-----------------------------------------------------------------//
	// 頂点関連関数
	//-----------------------------------------------------------------//

	/**
	* 2Dの頂点(4つ)を生成する関数
	* @param[in] rSize	サイズ
	* @param[in] rUV	UV
	* @return	登録した頂点のID
	*/
	virtual int CreateVertex2D(const fRect& rSize, const fRect& rUV)override;

	/** 
	* サイズ情報を設定する関数
	* @param[in] vtxID	設定したいVertexのID
	* @param[in] rSize	設定したいサイズ
	*/
	virtual void SetVtxSize(int vtxID, const fRect& rSize)override;

	/**
	* UV情報を設定する関数
	* @param[in] vtxID	設定したいVertexのID
	* @param[in] rUv	設定したいUV値
	*/
	virtual void SetVtxUV(int vtxID, const fRect& rUv)override;

	/**
	* 色情報を設定する関数
	* @param[in] vtxID		設定したいVertexのID
	* @param[in] red		設定したいr値
	* @param[in] green		設定したいg値
	* @param[in] blue		設定したいb値
	* @param[in] alpha		設定したいアルファ値
	*/
	virtual void SetVtxColor(int vtxID, float red, float green, float blue, float alpha)override;

	/** 
	* VertexのサイズのデータをRect構造体で取得する関数
	* @param[in] vtxID		サイズデータを取得したいVertexのID
	* @return サイズデーやを格納したRect構造体
	*/
	virtual fRect GetSizeRect(int vtxID)override;

	/** 
	* 指定した2D頂点バッファを解放する関数
	* @param[in] vtxID 解放したい頂点のID
 	*/
	virtual void ReleaseVertex2D(int vtxID)override;

	/** 登録している頂点バッファ(2D頂点バッファを含む)を全て解放する関数 */
	virtual void ReleaseVertexALL(void)override;

	//-----------------------------------------------------------------//
	// 描画関連関数
	//-----------------------------------------------------------------//
	
	/**
	* ステンシルテストを設定する関数
	* @param[in] isisStencilTest	true→ステンシルテストON, false→ステンシルテストOFF
	*/
	virtual void SetDepthStencilTest(bool isStencilTest)override;

	/** 描画開始処理 */
	virtual void StartRender(void)override;

	/** 描画終了処理 */
	virtual void EndRender(void)override;

	/** 
	* 2D描画関数
	* @todo とりあえず描画チェックの為実装。後で見直し
	* @param[in] rID	登録した頂点情報IDとテクスチャーID
	* @param[in] rPos	位置座標
	* @param[in] rScale	スケール値. デフォルトは1.0f,1.0f,1.0f
	* @param[in] angle	角度
	*/
	virtual void Draw2D(const DrawingID& rID, const SLVECTOR2& rPos, const SLVECTOR3& rScale = SLVECTOR3(1.0f, 1.0f, 1.0f), float angle = 0.0f)override;

	//-----------------------------------------------------------------//
	// インプットデバイス関連関数
	//-----------------------------------------------------------------//

	/** インプットデバイス更新関数 */
	virtual void UpdateInputDevice(void)override;

	/** 
	* キーの状態をチェックする関数 
	* @param[in] keyID キーのID slInputEnum.hのKEY_TYPE
	* @return	キーの状態. 状態の種類に関しては Common/slInputEnum.hを参照すること
	*/
	virtual DEVICE_STATE CheckKey(int keyID)override;

	/** 
	* ゲームパッドの状態をチェックする関数 
	* @param[in] padPartID	チェックしたいパッドのアクションID. XIGAMEPAD_ACTION_ID参照
	* @param[in] padNum		チェックしたいゲームパッドの番号.デフォルトは0
	* @return ゲームパッドの状態. 状態の種類に関しては Common/slInputEnum.hを参照すること
	*/
	virtual DEVICE_STATE CheckGamePad(int actionID, int  padNum = 0)override;

	/** 
	* ボタンなどを指定したIDで登録する関数 
	* @param[in] ID			登録したいID
	* @param[in] device		デバイスタイプ
	* @param[in] inputType	登録したいインプットタイプ	
	*/
	virtual void RegisterCustomizeType(int ID, HID_TYPE device, int inputType)override;

	/** 
	* カスタマイズしたボタンの状態チェック関数
	* @param[in] ID				登録したID
	* @param[in] checkState		チェックしたいデバイス状態.状態の種類に関しては Common/slInputEnum.hを参照すること
	* @param[in] deviceNum		デバイス番号.デフォルトは0
	* @return	その状態かどうか true→チェックしたい状態である false →チェックしたい状態でない
	*/
	virtual bool CheckCustomizeState(int ID, DEVICE_STATE  checkState, int deviceNum = 0)override;

	//-----------------------------------------------------------------//
	// その他
	//-----------------------------------------------------------------//


private:
	dx11::Window*				m_pWindow;
	dx11::GraphicsDevice*		m_pGraphicsDevice;
	dx11::TextureManager*		m_pTextureManager;
	dx11::Vertex2DManager*		m_pVertex2DManager;
	di::InputManager*			m_pInputManager;
	xi::GamePad*				m_pGamePad;
	CustomizeInputManager*		m_pCustomizeInputManager;

};	// class DX11Library 

}	// namespace sl

#endif // SL_DX11_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
