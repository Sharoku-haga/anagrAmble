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
class UVAnimationManager;
class DirectSoundManager;

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

	/**
	* クライアント領域の矩形サイズを取得する関数
	* @return クライアント領域の矩形サイズ
	*/
	virtual fRect GetClientSize(void) override;

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
	* @return サイズデータを格納したRect構造体
	*/
	virtual fRect GetSizeRect(int vtxID)override;

	/** 
	* VertexのUVのデータをRect構造体で取得する関数
	* @param[in] vtxID		UVデータを取得したいVertexのID
	* @return UVデータを格納したRect構造体
	*/
	virtual fRect GetUVRect(int vtxID)override;

	/** 
	* 指定した2D頂点バッファを解放する関数
	* @param[in] vtxID 解放したい頂点のID
 	*/
	virtual void ReleaseVertex2D(int vtxID)override;

	/** 登録している頂点バッファ(2D頂点バッファを含む)を全て解放する関数 */
	virtual void ReleaseVertexALL(void)override;

	//-----------------------------------------------------------------//
	// アニメーション関連関数
	//-----------------------------------------------------------------//
	/** 
	* UVアニメーションを登録する関数
	* @param[in] vtxID			アニメーションと紐づけしたいバーテックスのID
	* @param[in] patternCount	アニメーションのパターン数
	* @param[in] repeat			アニメーションを繰り返すかどうかのフラグ true→繰り返す false→繰り返さない デフォルトはfalse
	* @return 登録したのアニメーションID
	*/
	virtual int RegisterUVAnimeID(int vtxID, int patternCount, bool repeat = false)override;

	/** 
	* UVアニメーションを生成する関数
	* @param[in] vtxID				バーテックスのID
	* @param[in] animeID			アニメーションのID
	* @param[in] tuCount			tu方向のカウント数
	* @param[in] tvCount			tv方向のカウント数
	* @param[in] rBasicUV			基本となるUV値. この値を基本として増やして行く
	* @param[in] dispFlameCount		アニメーションの表示フレーム数
	*/
	virtual void CreateUVAnimeData(int vtxID, int animeID, int tuCount, int tvCount
							, const sl::fRect& rStartUVVal, int dispFlameCount)override;

	/**
	* アニメーション更新関数
	* UVアニメーションを更新する関数.
	* @param[in] vtxID		アニメーションを更新したいバーテックスのID
	* @param[in] animeID	更新したいアニメーションのID
	* @return アニメーションが更新したかどうか true→更新した false→更新していない.
	*/
	virtual void UpdateUVAnime(int vtxID, int animeID)override;

	/**
	* アニメーションを初期状態に戻す関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	*/
	virtual void ReturnUVAnimeInitialState(int vtxID, int animeID)override;

	/**
	* 現在のアニメーションが最後の番号かどうか確認する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @return アニメーションが最後の番号かどうか true→最後の番号である false →最後の番号でない 
	*/
	virtual bool CheckLastNumCurrnttUVAnime(int vtxID, int animeID)override;

	/**
	* Setter UVアニメーションデータを設定する関数
	* @param[in] vtxID				バーテックスのID
	* @param[in] animeID			アニメーションのID
	* @param[in] index				設定したいm_AnimeDataのインデックス
	* @param[in] rUV				設定したいUV値
	* @param[in] dispFlameCount		設定したいアニメーションを表示するフレーム数
	*/
	virtual void SetUVAnimeData(int vtxID, int animeID, int index
								, const sl::fRect& rUV, int dispFlameCount)override;

	/**
	* Setter UVアニメーションの順番を設定する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @param[in] rAnimeOrder	アニメーションの順番を格納している配列
	*/
	virtual void SeUVtAnimeOrder(int vtxID, int animeID, const std::vector<int>& rAnimeOrder)override;

	/** UVアニメデータを全て解放する関数 */
	virtual void  ReleaseUVAnimeDataALL(void)override;

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
	virtual void Draw2D(const DrawingID& rID, const SLVECTOR2& rPos
						, const SLVECTOR3& rScale = SLVECTOR3(1.0f, 1.0f, 1.0f), float angle = 0.0f)override;

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
	// 音関連関数
	//-----------------------------------------------------------------//

	/**
	* 音楽を読み込む関数.
	* @param[in]	id			登録したいID
	* @param[in]	pFilepath	音楽ファイル名
	* @return		結果 true→成功 false→失敗
	*/
	virtual bool LoadSound(int id, TCHAR* pFilePath)override;

	/**
	* 音を再生する関数
	* @param[in]	soundId			登録したサウンドID
	* @param[in]	soundMode		音の再生方式
	*/
	virtual void PlayBackSound(int soundId, int soundMode)override; 

	/**
	* 登録しているサウンドを解放関数
	* @param[in] soundId 登録したID
	*/
	virtual void ReleaseSound(int soundId)override;

	/** 登録しているサウンド全てを解放する関数 */
	virtual void ReleaseSoundALL(void)override;

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
	UVAnimationManager*			m_pUVAnimationManager;
	DirectSoundManager*			m_pDirectSoundManager;

};	// class DX11Library 

}	// namespace sl

#endif // SL_DX11_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
