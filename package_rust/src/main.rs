use hound;
mod ALGO; 
use ALGO::AlgoEngine;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    const INPUT_CHANNELS: usize = 4;
    const OUTPUT_CHANNELS: usize = 1;

    let mut reader = hound::WavReader::open("input.wav")?;
    let spec = reader.spec();

    if spec.channels as usize != INPUT_CHANNELS {
        panic!("Input WAV must have {} channels.", INPUT_CHANNELS);
    }

    let mut out_spec = spec;
    out_spec.channels = OUTPUT_CHANNELS as u16; 
    let mut writer = hound::WavWriter::create("output.wav", out_spec)?;
    
    const SAMPLES_PER_CHANNEL: usize = 128; 
    const INPUT_CHUNK_SIZE: usize = SAMPLES_PER_CHANNEL * INPUT_CHANNELS; 
    const OUTPUT_CHUNK_SIZE: usize = SAMPLES_PER_CHANNEL;              

    let mut input_buffer = vec![0i16; INPUT_CHUNK_SIZE];
    let mut output_buffer = vec![0i16; OUTPUT_CHUNK_SIZE]; 

    let mut samples_iter = reader.samples::<i16>();

    let engine = AlgoEngine::new();
    loop {
        let mut read_count = 0;

        let current_chunk = samples_iter.by_ref().take(INPUT_CHUNK_SIZE);

        for (slot, sample) in input_buffer.iter_mut().zip(current_chunk) {
            *slot = sample?;
            read_count += 1;
        }

        if read_count == 0 { break; }

        if read_count < INPUT_CHUNK_SIZE {
            input_buffer[read_count..].fill(0);
        }

        engine.process_i16(&input_buffer, &mut output_buffer);

        let frames_read = read_count / INPUT_CHANNELS;
        for &s in &output_buffer[..frames_read] {
            writer.write_sample(s)?;
        }
    }

    writer.finalize()?;
    Ok(())
}