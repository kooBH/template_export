
use hound;
use std::path::Path;

mod ALGO;
use ALGO::AlgoEngine;

fn main() -> Result<(), Box<dyn std::error::Error>>{
    // 1. WAV 파일 및 엔진 초기화
    let mut reader = hound::WavReader::open("input.wav")?;
    let spec = reader.spec();
    let mut writer = hound::WavWriter::create("output.wav", spec)?;
    let engine = AlgoEngine::new();

    // 128 샘플 크기의 고정 버퍼 설정
    const CHUNK_SIZE: usize = 128;
    let mut input_buffer = vec![0i16; CHUNK_SIZE];
    let mut output_buffer = vec![0i16; CHUNK_SIZE];

    // 2. 실시간 처리 루프
    let mut samples_iter = reader.samples::<i16>();
    let mut eof = false;

    while !eof {
        let mut read_count = 0;

        for i in 0..CHUNK_SIZE {
            match samples_iter.next() {
                Some(s) => {
                    input_buffer[i] = s?;
                    read_count += 1;
                }
                None => {
                    eof = true;
                    break;
                }
            }
        }

        if read_count == 0 { break; }

        if read_count < CHUNK_SIZE {
            for i in read_count..CHUNK_SIZE {
                input_buffer[i] = 0;
            }
        }

        engine.process_i16(&input_buffer, &mut output_buffer);

        for i in 0..read_count {
            writer.write_sample(output_buffer[i])?;
        }
    }

    writer.finalize()?;
    println!("Real-time block processing (128 samples) finished.");
    Ok(())
}