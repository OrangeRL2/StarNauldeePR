#include "AudioManager.h"

Microsoft::WRL::ComPtr<IXAudio2>AudioManager::xAudio2_;
IXAudio2MasteringVoice* AudioManager::masterVoice_;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	xAudio2_.Reset();
	delete[] soundData_.pBuffer;

	soundData_.pBuffer = 0;
	soundData_.bufferSize = 0;
	soundData_.wfex = {};
}

AudioManager* AudioManager::GetInstance()
{
	//関数内共通の変数として宣言
	static AudioManager instance;
	return &instance;

}

void AudioManager::StaticInitialize()
{

	HRESULT result;
	result = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	result = xAudio2_->CreateMasteringVoice(&masterVoice_);

}

void AudioManager::SoundLoadWave(const char* filename) {
	std::ifstream file;
	file.open(filename, std::ios_base::binary);

	assert(file.is_open());

	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));

	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	FormatChunk format = {};

	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	ChunkHeader data;
	file.read((char*)&data, sizeof(data));

	if (strncmp(data.id, "bext", 4) == 0) {

		file.seekg(data.size, std::ios_base::cur);

		file.read((char*)&data, sizeof(data));
	}


	if (strncmp(data.id, "JUNK", 4) == 0) {

		file.seekg(data.size, std::ios_base::cur);

		file.read((char*)&data, sizeof(data));
	}


	if (strncmp(data.id, "junk", 4) == 0) {

		file.seekg(data.size, std::ios_base::cur);

		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "LIST", 4) == 0) {

		file.seekg(data.size, std::ios_base::cur);

		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}


	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);


	file.close();

	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	soundData_ = soundData;

}

void AudioManager::SoundUnload() {

	xAudio2_.Reset();




}

void AudioManager::SoundPlayWave(bool loop, float volume) {
	HRESULT result;

	if (isPlay) {
		return;
	}

	isPlay = true;


	result = xAudio2_->CreateSourceVoice(&pSourceVoice, &soundData_.wfex);
	assert(SUCCEEDED(result));


	buf.pAudioData = soundData_.pBuffer;
	buf.AudioBytes = soundData_.bufferSize;

	pSourceVoice->SetVolume(volume);

	if (loop)
	{
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	buf.Flags = XAUDIO2_END_OF_STREAM;

	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();

}

void AudioManager::StopWave()
{
	HRESULT result;
	if (pSourceVoice != nullptr)
	{
		result = pSourceVoice->Stop();
		result = pSourceVoice->FlushSourceBuffers();
		result = pSourceVoice->SubmitSourceBuffer(&buf);

		isPlay = false;
	}
}